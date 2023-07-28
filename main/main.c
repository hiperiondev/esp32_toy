/*
 * Copyright 2023 Emiliano Gonzalez (egonzalez . hiperion @ gmail . com))
 * * Project Site: https://github.com/hiperiondev/esp32_toy *
 *
 * This is based on other projects:
 *    Toy programming language (https://github.com/Ratstail91/Toy)
 *    Others (see individual files)
 *
 *    please contact their authors for more information.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "linenoise/linenoise.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"

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

#include "toy_lib_about.h"
#include "toy_lib_random.h"
#include "toy_lib_runner.h"
#include "toy_lib_standard.h"
#include "esp32_toy_lib_wifi.h"

static char TAG[] = "main";
TaskHandle_t toytsk_handle;
TaskHandle_t ftpservertsk_handle;

#define WIFI_SSID "test"
#define WIFI_PASS "test1234"
#define CONSOLE_UART_CHANNEL UART_NUM_0

void interpret_line(Toy_Interpreter *interpreter, const char *source) {
    Toy_Lexer lexer;
    Toy_Parser parser;
    Toy_Compiler compiler;

    Toy_initLexer(&lexer, source);
    Toy_initParser(&parser, &lexer);
    Toy_initCompiler(&compiler);

    Toy_ASTNode *node = Toy_scanParser(&parser);
    Toy_writeCompiler(&compiler, node);

    size_t size = 0;
    const unsigned char *bytecode = Toy_collateCompiler(&compiler, &size);

    Toy_runInterpreter(interpreter, bytecode, size);

    Toy_freeASTNode(node);
    Toy_freeParser(&parser);
    Toy_freeCompiler(&compiler);
}

void toy_task(void *arg) {
    int probe_status;
    char *line = NULL;
    bool error;

    Toy_Lexer lexer;
    Toy_Parser parser;
    Toy_Compiler compiler;
    Toy_Interpreter interpreter;

    ///////////////////////////////////////////////////////

    // Initialize VFS & UART so we can use std::cout/cin
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    // Install UART driver for interrupt-driven reads and writes
    ESP_ERROR_CHECK(uart_driver_install( (uart_port_t)CONSOLE_UART_CHANNEL, 256, 0, 0, NULL, 0 ));

    // Tell VFS to use UART driver
    esp_vfs_dev_uart_use_driver(CONSOLE_UART_CHANNEL);
    esp_vfs_dev_uart_port_set_rx_line_endings(CONSOLE_UART_CHANNEL, ESP_LINE_ENDINGS_CR);
    // Move the caret to the beginning of the next line on '\n'
    esp_vfs_dev_uart_port_set_tx_line_endings(CONSOLE_UART_CHANNEL, ESP_LINE_ENDINGS_CRLF);

    probe_status = linenoiseProbe();
    if (probe_status) {
        // zero indicates success
        linenoiseSetDumbMode(1);
        printf("\r\n"
                "Your terminal application does not support escape sequences.\n\n"
                "Line editing and history features are disabled.\n\n"
                "On Windows, try using Putty instead.\r\n");

    } else {
        //printf("\033[2J\033[1H");
        printf("\n");
    }

    ///////////////////////////////////////////////////////

    Toy_initInterpreter(&interpreter);

    //inject the libs
    Toy_injectNativeHook(&interpreter, "about", Toy_hookAbout);
    Toy_injectNativeHook(&interpreter, "standard", Toy_hookStandard);
    Toy_injectNativeHook(&interpreter, "random", Toy_hookRandom);
    Toy_injectNativeHook(&interpreter, "runner", Toy_hookRunner);
    Toy_injectNativeHook(&interpreter, "wifi", Toy_hookWifi);

    ///////////////////////////////////////////////////////

    interpret_line(&interpreter, "print \"Toy start: OK\n\";");

    ///////////////////////////////////////////////////////

    while ((line = linenoise(TOY_CC_NOTICE "Toy> " TOY_CC_RESET)) != NULL) {
        if (line[0] != '\0' && line[0] != '/') {
            interpret_line(&interpreter, line);

            linenoiseHistoryAdd(line);
            linenoiseFree(line);
        }
    }

    Toy_freeInterpreter(&interpreter);
    vTaskDelete(NULL);
}

void app_main(void) {
    nvs_flash_init();
    fs_init();

    ESP_LOGI(TAG, "Connect WIFI\n");
    wifi_connect_sta(WIFI_SSID, WIFI_PASS);

    ESP_LOGI(TAG, "Create FTP server task");
    ftpserver_start("test", "test", "/littlefs");

    xTaskCreatePinnedToCore(
            toy_task,
            "toy_task",
            55000,
            NULL,
            10,
            &toytsk_handle,
            0
    );
}
