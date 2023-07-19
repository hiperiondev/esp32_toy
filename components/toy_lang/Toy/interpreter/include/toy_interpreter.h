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
 * @brief
 *
 */
typedef struct Toy_Interpreter {
    //input
    const unsigned char *bytecode; /**< */
    int length;                    /**< */
    int count;                     /**< */
    int codeStart;                 /**< */ //BUGFIX: for jumps, must be initialized to -1
    Toy_LiteralArray literalCache; /**< */ //read-only - built from the bytecode, refreshed each time new bytecode is provided

    //operation
    Toy_Scope *scope;
    Toy_LiteralArray stack;        /**< */

    //Library APIs
    Toy_LiteralDictionary *hooks;  /**< */

    //debug outputs
    Toy_PrintFn printOutput;       /**< */
    Toy_PrintFn assertOutput;      /**< */
    Toy_PrintFn errorOutput;       /**< */

    int depth; //don't overflow
    bool panic;
} Toy_Interpreter;

//native API
/**
 * @fn bool Toy_injectNativeFn(Toy_Interpreter *interpreter, const char *name, Toy_NativeFn func)
 * @brief
 *
 * @param interpreter
 * @param name
 * @param func
 * @return
 */
TOY_API bool Toy_injectNativeFn(Toy_Interpreter *interpreter, const char *name, Toy_NativeFn func);

/**
 * @fn bool Toy_injectNativeHook(Toy_Interpreter *interpreter, const char *name, Toy_HookFn hook)
 * @brief
 *
 * @param interpreter
 * @param name
 * @param hook
 * @return
 */
TOY_API bool Toy_injectNativeHook(Toy_Interpreter *interpreter, const char *name, Toy_HookFn hook);

/**
 * @fn bool Toy_callLiteralFn(Toy_Interpreter *interpreter, Toy_Literal func, Toy_LiteralArray *arguments, Toy_LiteralArray *returns)
 * @brief
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
 * @brief
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
 * @brief
 *
 * @param interpreter
 * @param literalPtr
 * @return
 */
TOY_API bool Toy_parseIdentifierToValue(Toy_Interpreter *interpreter, Toy_Literal *literalPtr);

/**
 * @fn void Toy_setInterpreterPrint(Toy_Interpreter *interpreter, Toy_PrintFn printOutput)
 * @brief
 *
 * @param interpreter
 * @param printOutput
 */
TOY_API void Toy_setInterpreterPrint(Toy_Interpreter *interpreter, Toy_PrintFn printOutput);

/**
 * @fn void Toy_setInterpreterAssert(Toy_Interpreter *interpreter, Toy_PrintFn assertOutput)
 * @brief
 *
 * @param interpreter
 * @param assertOutput
 */
TOY_API void Toy_setInterpreterAssert(Toy_Interpreter *interpreter, Toy_PrintFn assertOutput);

/**
 * @fn void Toy_setInterpreterError(Toy_Interpreter *interpreter, Toy_PrintFn errorOutput)
 * @brief
 *
 * @param interpreter
 * @param errorOutput
 */
TOY_API void Toy_setInterpreterError(Toy_Interpreter *interpreter, Toy_PrintFn errorOutput);

//main access
/**
 * @fn void Toy_initInterpreter(Toy_Interpreter *interpreter)
 * @brief
 *
 * @param interpreter
 */
TOY_API void Toy_initInterpreter(Toy_Interpreter *interpreter); //start of program

/**
 * @fn void Toy_runInterpreter(Toy_Interpreter *interpreter, const unsigned char *bytecode, size_t length)
 * @brief
 *
 * @param interpreter
 * @param bytecode
 * @param length
 */
TOY_API void Toy_runInterpreter(Toy_Interpreter *interpreter, const unsigned char *bytecode, size_t length); //run the code

/**
 * @fnvoid Toy_resetInterpreter(Toy_Interpreter *interpreter)
 * @brief
 *
 * @param interpreter
 */
TOY_API void Toy_resetInterpreter(Toy_Interpreter *interpreter); //use this to reset the interpreter's environment between runs

/**
 * @fn void Toy_freeInterpreter(Toy_Interpreter *interpreter)
 * @brief
 *
 * @param interpreter
 */
TOY_API void Toy_freeInterpreter(Toy_Interpreter *interpreter); //end of program

#endif /* TOY_INTERPRETER_H_ */
