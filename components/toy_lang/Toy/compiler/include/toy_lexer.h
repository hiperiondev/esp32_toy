/**
 * @file toy_lexer.h
 * @brief @@???@@
 *
 */

#ifndef TOY_LEXER_H_
#define TOY_LEXER_H_

#include <stdbool.h>

#include "toy_common.h"
#include "toy_token_types.h"

//lexers are bound to a string of code, and return a single token every time scan is called
/**
 * @typedef Toy_Lexer
 * @brief @@???@@
 *
 */
typedef struct {
    const char *source;
    int start;            /**< start of the token */
    int current;          /**< current position of the lexer */
    int line;             /**< track this for error handling */
    bool commentsEnabled; /**< BUGFIX: enable comments (disabled in repl) */
} Toy_Lexer;

//tokens are intermediaries between lexers and parsers
/**
 * @struct Toy_Token
 * @brief @@???@@
 *
 */
typedef struct {
    Toy_TokenType type; /**< @@???@@ */
    const char *lexeme; /**< @@???@@ */
    int length;         /**< @@???@@ */
    int line;           /**< @@???@@ */
} Toy_Token;

/**
 * @fn void Toy_initLexer(Toy_Lexer *lexer, const char *source)
 * @brief Initializes a lexer, binding it to the source parameter; the lexer is now ready to be passed to the parser.
 *
 * @param lexer
 * @param source
 */
TOY_API void Toy_initLexer(Toy_Lexer *lexer, const char *source);

/**
 * @fn Toy_Token Toy_private_scanLexer(Toy_Lexer *lexer)
 * @brief @@???@@
 *
 * @param lexer
 * @return
 */
TOY_API Toy_Token Toy_private_scanLexer(Toy_Lexer *lexer);

//for debugging
/**
 * @fn void Toy_private_printToken(Toy_Token *token)
 * @brief @@???@@
 *
 * @param token
 */
TOY_API void Toy_private_printToken(Toy_Token *token);

/**
 * @fn void Toy_private_setComments(Toy_Lexer *lexer, bool enabled)
 * @brief @@???@@
 *
 * @param lexer
 * @param enabled
 */
TOY_API void Toy_private_setComments(Toy_Lexer *lexer, bool enabled);

#endif /* TOY_LEXER_H_ */
