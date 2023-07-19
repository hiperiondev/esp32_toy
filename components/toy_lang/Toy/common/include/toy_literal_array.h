#ifndef TOY_LITERAL_ARRAY_H_
#define TOY_LITERAL_ARRAY_H_

#include <stdbool.h>

#include "toy_common.h"
#include "toy_literal.h"

/**
 * @struct Toy_LiteralArray
 * @brief
 *
 */
typedef struct Toy_LiteralArray {
    Toy_Literal *literals; /**< */
    int capacity;          /**< */
    int count;             /**< */
} Toy_LiteralArray;

/**
 * @fn void Toy_initLiteralArray(Toy_LiteralArray *array)
 * @brief
 *
 * @param array
 */
TOY_API void Toy_initLiteralArray(Toy_LiteralArray *array);

/**
 * @fn void Toy_freeLiteralArray(Toy_LiteralArray *array)
 * @brief
 *
 * @param array
 */
TOY_API void Toy_freeLiteralArray(Toy_LiteralArray *array);

/**
 * @fn int Toy_pushLiteralArray(Toy_LiteralArray *array, Toy_Literal literal)
 * @brief
 *
 * @param array
 * @param literal
 * @return
 */
TOY_API int Toy_pushLiteralArray(Toy_LiteralArray *array, Toy_Literal literal);

/**
 * @fn Toy_Literal Toy_popLiteralArray(Toy_LiteralArray *array)
 * @brief
 *
 * @param array
 * @return
 */
TOY_API Toy_Literal Toy_popLiteralArray(Toy_LiteralArray *array);

/**
 * @fn bool Toy_setLiteralArray(Toy_LiteralArray *array, Toy_Literal index, Toy_Literal value)
 * @brief
 *
 * @param array
 * @param index
 * @param value
 * @return
 */
TOY_API bool Toy_setLiteralArray(Toy_LiteralArray *array, Toy_Literal index, Toy_Literal value);

/**
 * @fn Toy_Literal Toy_getLiteralArray(Toy_LiteralArray *array, Toy_Literal index)
 * @brief
 *
 * @param array
 * @param index
 * @return
 */
TOY_API Toy_Literal Toy_getLiteralArray(Toy_LiteralArray *array, Toy_Literal index);

/**
 * @fn int Toy_findLiteralIndex(Toy_LiteralArray *array, Toy_Literal literal)
 * @brief
 *
 * @param array
 * @param literal
 * @return
 */
int Toy_findLiteralIndex(Toy_LiteralArray *array, Toy_Literal literal);

//TODO: add a function to get the capacity & count

#endif /* TOY_LITERAL_ARRAY_H_ */
