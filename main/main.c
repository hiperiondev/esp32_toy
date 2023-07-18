/*
 * @file main.c
 *
 * @brief main program
 * @details
 * This is based on other projects:
 *   HALFRED ver. 0.2.0 [bsd license: see LICENSE-HALFRED.txt](http://www.wsn.agh.edu.pl/download/public/halfred/0.2.0/)
 *   Others (see individual files)
 *
 *   please contact their authors for more information.
 *
 * @author Emiliano Gonzalez (egonzalez . hiperion @ gmail . com))
 * @version 0.1
 * @date 2023
 * @copyright MIT License
 * @see https://github.com/hiperiondev/esp32-microvium
 */

#define LOG_LOCAL_LEVEL ESP_LOG_INFO

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <esp_err.h>
#include <esp_log.h>

#include "nvs.h"
#include "nvs_flash.h"
#include "hal_fs.h"
#include "hal_wifi.h"
#include "esp_partition.h"
#include "ftpserver.h"

#include "toy_lexer.h"
#include "toy_parser.h"
#include "toy_compiler.h"
#include "toy_interpreter.h"
#include "toy_console_colors.h"
#include "toy_memory.h"
#include "toy_repl_tools.h"

static char TAG[] = "main";
TaskHandle_t toytsk_handle;
TaskHandle_t ftpservertsk_handle;

#define WIFI_SSID "test"
#define WIFI_PASS "test1234"

//suppress the print output
static void noPrintFn(const char *output) {
    //NO OP
}

int ignoredAssertions = 0;
static void noAssertFn(const char *output) {
    if (strncmp(output, "!ignore", 7) == 0) {
        ignoredAssertions++;
    } else {
        printf(TOY_CC_ERROR "Assertion failure: ");
        printf("%s", output);
        printf("\n" TOY_CC_RESET); //default new line
    }
}

void runBinaryCustom(const unsigned char *tb, size_t size) {
    Toy_Interpreter interpreter;
    Toy_initInterpreter(&interpreter);

    //NOTE: suppress print output for testing
    Toy_setInterpreterPrint(&interpreter, noPrintFn);
    Toy_setInterpreterAssert(&interpreter, noAssertFn);

    Toy_runInterpreter(&interpreter, tb, size);
    Toy_freeInterpreter(&interpreter);
}

void runSourceCustom(const char *source) {
    size_t size = 0;
    const unsigned char *tb = Toy_compileString(source, &size);
    if (!tb) {
        return;
    }
    runBinaryCustom(tb, size);
}

void runSourceFileCustom(const char *fname) {
    size_t size = 0; //not used
    const char *source = (const char*) Toy_readFile(fname, &size);
    runSourceCustom(source);
    free((void*) source);
}

void toy_task(void *pvParameter) {
    // test compiler
    {
        //test init & free
        Toy_Compiler compiler;
        Toy_initCompiler(&compiler);
        Toy_freeCompiler(&compiler);
    }

    {
        //source
        char *source = "print null;";

        //test basic compilation & collation
        Toy_Lexer lexer;
        Toy_Parser parser;
        Toy_Compiler compiler;

        Toy_initLexer(&lexer, source);
        Toy_initParser(&parser, &lexer);
        Toy_initCompiler(&compiler);

        Toy_ASTNode *node = Toy_scanParser(&parser);

        //write
        Toy_writeCompiler(&compiler, node);

        //collate
        size_t size = 0;
        unsigned char *bytecode = Toy_collateCompiler(&compiler, &size);

        //cleanup
        TOY_FREE_ARRAY(unsigned char, bytecode, size);
        Toy_freeASTNode(node);
        Toy_freeParser(&parser);
        Toy_freeCompiler(&compiler);
    }

    {
        //source
        size_t sourceLength = 0;
        const char *source = (const char*) Toy_readFile("compiler_sample_code.toy", &sourceLength);

        //test basic compilation & collation
        Toy_Lexer lexer;
        Toy_Parser parser;
        Toy_Compiler compiler;

        Toy_initLexer(&lexer, source);
        Toy_initParser(&parser, &lexer);
        Toy_initCompiler(&compiler);

        Toy_ASTNode *node = Toy_scanParser(&parser);
        while (node != NULL) {
            if (node->type == TOY_AST_NODE_ERROR) {
                printf(TOY_CC_ERROR "ERROR: Error node found" TOY_CC_RESET);
                goto end;
            }

            //write
            Toy_writeCompiler(&compiler, node);
            Toy_freeASTNode(node);

            node = Toy_scanParser(&parser);
        }

        //collate
        size_t size = 0;
        unsigned char *bytecode = Toy_collateCompiler(&compiler, &size);

        //cleanup
        TOY_FREE_ARRAY(char, source, sourceLength);
        TOY_FREE_ARRAY(unsigned char, bytecode, size);
        Toy_freeParser(&parser);
        Toy_freeCompiler(&compiler);
    }

    printf(TOY_CC_NOTICE "COMPILER: All good\n" TOY_CC_RESET);

    // test interpreter
    {
        //test init & free
        Toy_Interpreter interpreter;
        Toy_initInterpreter(&interpreter);
        Toy_freeInterpreter(&interpreter);
    }

    {
        //source
        const char *source = "print null;";

        //test basic compilation & collation
        Toy_Lexer lexer;
        Toy_Parser parser;
        Toy_Compiler compiler;
        Toy_Interpreter interpreter;

        Toy_initLexer(&lexer, source);
        Toy_initParser(&parser, &lexer);
        Toy_initCompiler(&compiler);
        Toy_initInterpreter(&interpreter);

        Toy_ASTNode *node = Toy_scanParser(&parser);

        //write
        Toy_writeCompiler(&compiler, node);

        //collate
        size_t size = 0;
        const unsigned char *bytecode = Toy_collateCompiler(&compiler, &size);

        //NOTE: suppress print output for testing
        Toy_setInterpreterPrint(&interpreter, noPrintFn);
        Toy_setInterpreterAssert(&interpreter, noAssertFn);

        //run
        Toy_runInterpreter(&interpreter, bytecode, size);

        //cleanup
        Toy_freeASTNode(node);
        Toy_freeParser(&parser);
        Toy_freeCompiler(&compiler);
        Toy_freeInterpreter(&interpreter);
    }

    {
        //run each file
        const char *filenames[] = {
                "arithmetic.toy",
                "casting-parentheses-bugfix.toy",
                "casting.toy",
                "coercions.toy",
                "comparisons.toy",
                "dot-and-matrix.toy",
                "dot-assignments-bugfix.toy",
                "dot-chaining.toy",
                "dot-modulo-bugfix.toy",
                "dottify-bugfix.toy",
                "function-within-function-bugfix.toy",
                "functions.toy",
                "increment-postfix-bugfix.toy",
                "index-arrays.toy",
                "index-assignment-both-bugfix.toy",
                "index-assignment-intermediate-bugfix.toy",
                "index-assignment-left-bugfix.toy",
                "index-dictionaries.toy",
                "index-strings.toy",
                "jumps.toy",
                "jumps-in-functions.toy",
                "logicals.toy",
                "long-array.toy",
                "long-dictionary.toy",
                "long-literals.toy",
                "native-functions.toy",
                "or-chaining-bugfix.toy",
                "panic-within-functions.toy",
                "polyfill-insert.toy",
                "polyfill-remove.toy",
                "short-circuiting-support.toy",
                "ternary-expressions.toy",
                "types.toy",
                NULL
        };

        for (int i = 0; filenames[i]; i++) {
            printf("Running %s\n", filenames[i]);

            char buffer[128];
            snprintf(buffer, 128, "%s", filenames[i]);

            runSourceFileCustom(buffer);
        }
    }

    //1, to allow for the assertion test
    if (ignoredAssertions > 1) {
        printf(TOY_CC_ERROR "Assertions hidden: %d\n", ignoredAssertions);
        goto end;
    }

    printf(TOY_CC_NOTICE "INTERPRETER: All good\n" TOY_CC_RESET);

    end:
    while (1)
        vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void app_main() {
    nvs_flash_init();
    fs_init();

    ESP_LOGI(TAG, "Connect WIFI\n");
    wifi_connect_sta(WIFI_SSID, WIFI_PASS);

    ESP_LOGI(TAG, "Create FTP server task");
    ftpserver_start("test", "test", "/littlefs");

    xTaskCreatePinnedToCore(
            toy_task,
            "toy_task",
            15000,
            NULL,
            10,
            &toytsk_handle,
            0
    );
}
