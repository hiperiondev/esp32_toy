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
typedef struct Toy_Interpreter {
    //input
    const unsigned char *bytecode;
    int length;
    int count;
    int codeStart; //BUGFIX: for jumps, must be initialized to -1
    Toy_LiteralArray literalCache; //read-only - built from the bytecode, refreshed each time new bytecode is provided

    //operation
    Toy_Scope *scope;
    Toy_LiteralArray stack;

    //Library APIs
    Toy_LiteralDictionary *hooks;

    //debug outputs
    Toy_PrintFn printOutput;
    Toy_PrintFn assertOutput;
    Toy_PrintFn errorOutput;

    int depth; //don't overflow
    bool panic;
} Toy_Interpreter;

//native API
TOY_API bool Toy_injectNativeFn(Toy_Interpreter *interpreter, const char *name, Toy_NativeFn func);
TOY_API bool Toy_injectNativeHook(Toy_Interpreter *interpreter, const char *name, Toy_HookFn hook);

TOY_API bool Toy_callLiteralFn(Toy_Interpreter *interpreter, Toy_Literal func, Toy_LiteralArray *arguments, Toy_LiteralArray *returns);
TOY_API bool Toy_callFn(Toy_Interpreter *interpreter, const char *name, Toy_LiteralArray *arguments, Toy_LiteralArray *returns);

//utilities for the host program
TOY_API bool Toy_parseIdentifierToValue(Toy_Interpreter *interpreter, Toy_Literal *literalPtr);
TOY_API void Toy_setInterpreterPrint(Toy_Interpreter *interpreter, Toy_PrintFn printOutput);
TOY_API void Toy_setInterpreterAssert(Toy_Interpreter *interpreter, Toy_PrintFn assertOutput);
TOY_API void Toy_setInterpreterError(Toy_Interpreter *interpreter, Toy_PrintFn errorOutput);

//main access
TOY_API void Toy_initInterpreter(Toy_Interpreter *interpreter); //start of program
TOY_API void Toy_runInterpreter(Toy_Interpreter *interpreter, const unsigned char *bytecode, size_t length); //run the code
TOY_API void Toy_resetInterpreter(Toy_Interpreter *interpreter); //use this to reset the interpreter's environment between runs
TOY_API void Toy_freeInterpreter(Toy_Interpreter *interpreter); //end of program

#endif /* TOY_INTERPRETER_H_ */
