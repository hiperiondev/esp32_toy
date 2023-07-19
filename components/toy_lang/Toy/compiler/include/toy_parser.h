/**
 * @file toy_parser.h
 * @brief @@???@@
 *
 */

#ifndef TOY_PARSER_H_
#define TOY_PARSER_H_

#include <stdbool.h>

#include "toy_common.h"
#include "toy_lexer.h"
#include "toy_ast_node.h"

//DOCS: parsers are bound to a lexer, and turn the outputted tokens into AST nodes
/**
 * @typedef Toy_Parser
 * @brief @@???@@
 *
 */
typedef struct {
    Toy_Lexer* lexer;   /**< @@???@@ */
    bool error;         /**< I've had an error */
    bool panic;         /**< I am processing an error */

    //track the last two outputs from the lexer
    Toy_Token current;  /**< @@???@@ */
    Toy_Token previous; /**< @@???@@ */
} Toy_Parser;

/**
 * @fn void Toy_initParser(Toy_Parser* parser, Toy_Lexer* lexer)
 * @brief Initializes a Toy_Parser, binding the given Toy_Lexer to it.
 *
 * @param parser
 * @param lexer
 */
TOY_API void Toy_initParser(Toy_Parser* parser, Toy_Lexer* lexer);

/**
 * @fn void Toy_freeParser(Toy_Parser* parser)
 * @brief Frees a Toy_Parser once its task is completed.
 *
 * @param parser
 */
TOY_API void Toy_freeParser(Toy_Parser* parser);

/**
 * @fn Toy_ASTNode* Toy_scanParser(Toy_Parser* parser)
 * @brief Returns an abstract syntax tree representing part of the program, or an error node. The abstract syntax tree must be passed to Toy_writeCompiler and/or Toy_freeASTNode.
 *        This function should be called repeatedly until it returns NULL, indicating the end of the program.
 *
 * @param parser
 * @return
 */
TOY_API Toy_ASTNode* Toy_scanParser(Toy_Parser* parser);

#endif /* TOY_PARSER_H_ */
