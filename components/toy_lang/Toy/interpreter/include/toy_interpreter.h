/**
 * @file toy_interpreter.h
 * @brief @@???@@
 *
 */

#ifndef TOY_INTERPRETER_H_
#define TOY_INTERPRETER_H_

#include <stdbool.h>
#include <stddef.h>

#include "toy_common.h"
#include "toy_literal.h"
#include "toy_literal_array.h"
#include "toy_literal_dictionary.h"
#include "toy_scope.h"

//the interpreter acts depending on the bytecode instructions
/**
 * @typedef Toy_Interpreter
 * @brief @@???@@
 *
 */
typedef struct Toy_Interpreter {
    //input
    const unsigned char *bytecode; /**< @@???@@ */
    int length;                    /**< @@???@@ */
    int count;                     /**< @@???@@ */
    int codeStart;                 /**< BUGFIX: for jumps, must be initialized to -1 */
    Toy_LiteralArray literalCache; /**< read-only - built from the bytecode, refreshed each time new bytecode is provided */

    //operation
    Toy_Scope *scope;              /**< @@???@@ */
    Toy_LiteralArray stack;        /**< @@???@@ */

    //Library APIs
    Toy_LiteralDictionary *hooks;  /**< @@???@@ */

    //debug outputs
    Toy_PrintFn printOutput;       /**< @@???@@ */
    Toy_PrintFn assertOutput;      /**< @@???@@ */
    Toy_PrintFn errorOutput;       /**< @@???@@ */

    int depth;                     /**< don't overflow */
    bool panic;                    /**< @@???@@ */
} Toy_Interpreter;

//native API
/**
 * @fn bool Toy_injectNativeFn(Toy_Interpreter *interpreter, const char *name, Toy_NativeFn func)
 * @brief Will inject the given native function func into the Toy_Interpreter's current scope, with the name passed as name. Both the name and function will be converted into literals internally before being stored. It will return true on success, otherwise it will return false.
 *        The primary use of this function is within hooks.
 *
 * @param interpreter
 * @param name
 * @param func
 * @return
 */
TOY_API bool Toy_injectNativeFn(Toy_Interpreter *interpreter, const char *name, Toy_NativeFn func);

/**
 * @fn bool Toy_injectNativeHook(Toy_Interpreter *interpreter, const char *name, Toy_HookFn hook)
 * @brief Will inject the given native function hook into the Toy_Interpreter's hook cache, with the name passed in as name. Both the name and the function will be converted into literals internally before being stored. It will return true on success, otherwise it will return false.
 *
 * @param interpreter
 * @param name
 * @param hook
 * @return
 */
TOY_API bool Toy_injectNativeHook(Toy_Interpreter *interpreter, const char *name, Toy_HookFn hook);

/**
 * @fn bool Toy_callLiteralFn(Toy_Interpreter *interpreter, Toy_Literal func, Toy_LiteralArray *arguments, Toy_LiteralArray *returns)
 * @brief Calls a Toy_Literal which contains a function, with the arguments to that function passed in as arguments and the results stored in returns. It returns true on success, otherwise it returns false.
 *        The literal func can be either a native function or a Toy function, but it won't execute a hook.
 *
 * @param interpreter
 * @param func
 * @param arguments
 * @param returns
 * @return
 */
TOY_API bool Toy_callLiteralFn(Toy_Interpreter *interpreter, Toy_Literal func, Toy_LiteralArray *arguments, Toy_LiteralArray *returns);

/**
 * @fn bool Toy_callFn(Toy_Interpreter *interpreter, const char *name, Toy_LiteralArray *arguments, Toy_LiteralArray *returns)
 * @brief Utility function that will find a Toy_literal within the Toy_Interpreter's scope with a name that matches name, and will invoke it using Toy_callLiteralFn (passing in arguments and returns as expected).
 *
 * @param interpreter
 * @param name
 * @param arguments
 * @param returns
 * @return
 */
TOY_API bool Toy_callFn(Toy_Interpreter *interpreter, const char *name, Toy_LiteralArray *arguments, Toy_LiteralArray *returns);

//utilities for the host program
/**
 * @fn bool Toy_parseIdentifierToValue(Toy_Interpreter *interpreter, Toy_Literal *literalPtr)
 * @brief Sometimes, native functions will receive Toy_Literal identifiers instead of the values - the values can be retreived from the given interpreter's scope using the following pattern:
 *        Toy_Literal foobarIdn = foobar;
 *        if (TOY_IS_IDENTIFIER(foobar) && Toy_parseIdentifierToValue(interpreter, &foobar)) {
 *            freeLiteral(foobarIdn); //remember to free the identifier
 *        }
 *
 * @param interpreter
 * @param literalPtr
 * @return
 */
TOY_API bool Toy_parseIdentifierToValue(Toy_Interpreter *interpreter, Toy_Literal *literalPtr);

/**
 * @fn void Toy_setInterpreterPrint(Toy_Interpreter *interpreter, Toy_PrintFn printOutput)
 * @brief This function sets the function called by the print keyword. By default, the following wrapper is used:
 *        static void printWrapper(const char* output) {
 *            printf("%s\n", output);
 *        }
 *
 * @param interpreter
 * @param printOutput
 */
TOY_API void Toy_setInterpreterPrint(Toy_Interpreter *interpreter, Toy_PrintFn printOutput);

/**
 * @fn void Toy_setInterpreterAssert(Toy_Interpreter *interpreter, Toy_PrintFn assertOutput)
 * @brief Sets the function called by the assert keyword on failure. By default, the following wrapper is used:
 *        static void assertWrapper(const char* output) {
 *            fprintf(stderr, "Assertion failure: %s\n", output);
 *        }
 *
 * @param interpreter
 * @param assertOutput
 */
TOY_API void Toy_setInterpreterAssert(Toy_Interpreter *interpreter, Toy_PrintFn assertOutput);

/**
 * @fn void Toy_setInterpreterError(Toy_Interpreter *interpreter, Toy_PrintFn errorOutput)
 * @brief Sets the function called when an error occurs within the interpreter. By default, the following wrapper is used:
 *        static void errorWrapper(const char* output) {
 *            fprintf(stderr, "%s", output); //no newline
 *        }
 *
 * @param interpreter
 * @param errorOutput
 */
TOY_API void Toy_setInterpreterError(Toy_Interpreter *interpreter, Toy_PrintFn errorOutput);

//main access
/**
 * @fn void Toy_initInterpreter(Toy_Interpreter *interpreter)
 * @brief Initializes the Toy_Interpreter. It allocates memory for internal systems such as the stack, and zeroes-out systems that have yet to be invoked. Internally, it also invokes Toy_resetInterpreter to initialize the environment.
 *
 * @param interpreter
 */
TOY_API void Toy_initInterpreter(Toy_Interpreter *interpreter); //start of program

/**
 * @fn void Toy_runInterpreter(Toy_Interpreter *interpreter, const unsigned char *bytecode, size_t length)
 * @brief Takes a Toy_Interpreter and bytecode (as well as the length of the bytecode), checks its version information, parses and un-flattens the literal cache, and executes the compiled program stored in the bytecode. This function also consumes the bytecode, so the bytecode argument is no longer valid after calls.
 *        If the given bytecode's embedded version is not compatible with the current interpreter, then this function will refuse to execute.
 *        Re-using a Toy_Interpreter instance without first resetting it is possible (that's how the repl works), however doing so may have unintended consequences if the scripts are not intended to be used in such a way. Any variables declared will persist.
 *
 * @param interpreter
 * @param bytecode
 * @param length
 */
TOY_API void Toy_runInterpreter(Toy_Interpreter *interpreter, const unsigned char *bytecode, size_t length); //run the code

/**
 * @fn void Toy_resetInterpreter(Toy_Interpreter *interpreter)
 * @brief Frees any environment that the scripts have built up, and generates a new one. It also injects several globally available functions:
 * - set
 * - get
 * - push
 * - pop
 * - length
 * - clear
 *
 * @param interpreter
 */
TOY_API void Toy_resetInterpreter(Toy_Interpreter *interpreter); //use this to reset the interpreter's environment between runs

/**
 * @fn void Toy_freeInterpreter(Toy_Interpreter *interpreter)
 * @brief Frees a Toy_Interpreter, clearing all of the memory used within. That interpreter is no longer valid for use, and must be re-initialized.
 *
 * @param interpreter
 */
TOY_API void Toy_freeInterpreter(Toy_Interpreter *interpreter); //end of program

#endif /* TOY_INTERPRETER_H_ */
