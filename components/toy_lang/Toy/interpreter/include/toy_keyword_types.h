#ifndef TOY_KEYWORD_TYPES_H_
#define TOY_KEYWORD_TYPES_H_

#include "toy_token_types.h"

/**
 * @typedef Toy_KeywordType
 * @brief
 *
 */
typedef struct {
    Toy_TokenType type; /**< */
    char *keyword;      /**< */
} Toy_KeywordType;


extern Toy_KeywordType Toy_keywordTypes[]; /**< Toy_keywordTypes */

/**
 * @fn char* Toy_findKeywordByType(Toy_TokenType type)
 * @brief
 *
 * @param type
 * @return
 */
char* Toy_findKeywordByType(Toy_TokenType type);

/**
 * @fn Toy_TokenType Toy_findTypeByKeyword(const char *keyword)
 * @brief
 *
 * @param keyword
 * @return
 */
Toy_TokenType Toy_findTypeByKeyword(const char *keyword);

#endif /* TOY_KEYWORD_TYPES_H_ */
