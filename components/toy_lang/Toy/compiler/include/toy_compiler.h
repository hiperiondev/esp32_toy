/**
 * @file toy_compiler.h
 * @brief @@???@@
 *
 */

#ifndef TOY_COMPILER_H_
#define TOY_COMPILER_H_

#include <stdbool.h>
#include <stddef.h>

#include "toy_common.h"
#include "toy_opcodes.h"
#include "toy_ast_node.h"
#include "toy_literal_array.h"

//the compiler takes the nodes, and turns them into sequential chunks of bytecode, saving literals to an external array
/**
 * @typedef Toy_Compiler
 * @brief @@???@@
 *
 */
typedef struct Toy_Compiler {
    Toy_LiteralArray literalCache; /**< @@???@@ */
    unsigned char *bytecode;       /**< @@???@@ */
    int capacity;                  /**< @@???@@ */
    int count;                     /**< @@???@@ */
    bool panic;                    /**< @@???@@ */
} Toy_Compiler;

/**
 * @fn void Toy_initCompiler(Toy_Compiler *compiler)
 * @brief initializes the given Toy_Compiler.
 *
 * @param compiler
 */
TOY_API void Toy_initCompiler(Toy_Compiler *compiler);

/**
 * @fn void Toy_writeCompiler(Toy_Compiler *compiler, Toy_ASTNode *node
 * @brief Writes the given node argument to the compiler. During the writing step, this function may be called repeatedly, with a stream of results from Toy_scanParser, until Toy_scanParser returns NULL.
 *
 * @param compiler
 * @param node
 */
TOY_API void Toy_writeCompiler(Toy_Compiler *compiler, Toy_ASTNode *node);

/**
 * @fn void Toy_freeCompiler(Toy_Compiler *compiler)
 * @brief Frees a Toy_Compiler. Calling this on a compiler which has not been collated will free that compiler as expected - anything written to it will be lost.
 *
 * @param compiler
 */
TOY_API void Toy_freeCompiler(Toy_Compiler *compiler);

//embed the header, data section, code section, function section, etc.
/**
 * @fn unsigned char* Toy_collateCompiler(Toy_Compiler *compiler, size_t *size)
 * @brief Returns a buffer of bytes, known as "bytecode", created from the given Toy_Compiler; it also stores the size of the bytecode in the variable pointed to by size.
 *        Calling Toy_collateCompiler multiple times on the same compiler will produce undefined behaviour.
 *
 * @param compiler
 * @param size
 * @return
 */
TOY_API unsigned char* Toy_collateCompiler(Toy_Compiler *compiler, size_t *size);

#endif /* TOY_COMPILER_H_ */
