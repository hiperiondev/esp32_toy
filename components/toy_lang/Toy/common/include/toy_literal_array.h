/**
 * @file toy_literal_array.h
 * @brief @@????@@
 *
 */

#ifndef TOY_LITERAL_ARRAY_H_
#define TOY_LITERAL_ARRAY_H_

#include <stdbool.h>

#include "toy_common.h"
#include "toy_literal.h"

/**
 * @struct Toy_LiteralArray
 * @brief @@????@@
 *
 */
typedef struct Toy_LiteralArray {
    Toy_Literal *literals; /**< @@???@@ */
    int capacity; /**< @@???@@ */
    int count; /**< @@???@@ */
} Toy_LiteralArray;

/**
 * @fn void Toy_initLiteralArray(Toy_LiteralArray *array)
 * @brief initializes a Toy_LiteralArray pointed to by array.
 *
 * @param array
 */
TOY_API void Toy_initLiteralArray(Toy_LiteralArray *array);

/**
 * @fn void Toy_freeLiteralArray(Toy_LiteralArray *array)
 * @brief Frees a Toy_LiteralArray pointed to by array. Every literal within is passed to Toy_freeLiteral before its memory is released.
 *
 * @param array
 */
TOY_API void Toy_freeLiteralArray(Toy_LiteralArray *array);

/**
 * @fn int Toy_pushLiteralArray(Toy_LiteralArray *array, Toy_Literal literal)
 * @brief Adds a new literal to the end of the array, growing the array's internal buffer if needed.
 *
 * @param array
 * @param literal
 * @return index of the inserted value.
 */
TOY_API int Toy_pushLiteralArray(Toy_LiteralArray *array, Toy_Literal literal);

/**
 * @fn Toy_Literal Toy_popLiteralArray(Toy_LiteralArray *array)
 * @brief Removes the literal at the end of the array
 *
 * @param array
 * @return index of the deleted value.
 */
TOY_API Toy_Literal Toy_popLiteralArray(Toy_LiteralArray *array);

/**
 * @fn bool Toy_setLiteralArray(Toy_LiteralArray *array, Toy_Literal index, Toy_Literal value)
 * @brief Frees the literal at the position represented by the integer literal index, and stores value in its place.
 *
 * @param array
 * @param index
 * @param value
 * @return true on success, otherwise it returns false.
 */
TOY_API bool Toy_setLiteralArray(Toy_LiteralArray *array, Toy_Literal index, Toy_Literal value);

/**
 * @fn Toy_Literal Toy_getLiteralArray(Toy_LiteralArray *array, Toy_Literal index)
 * @brief Returns the literal at the position represented by the integer literal index, or returns a null literal if none is found.
 *        If index is not an integer literal or is out of bounds, this function returns a null literal.
 *
 * @param array
 * @param index
 * @return
 */
TOY_API Toy_Literal Toy_getLiteralArray(Toy_LiteralArray *array, Toy_Literal index);

/**
 * @fn int Toy_private_findLiteralIndex(Toy_LiteralArray *array, Toy_Literal literal)
 * @brief @@????@@
 *
 * @param array
 * @param literal
 * @return
 */
int Toy_private_findLiteralIndex(Toy_LiteralArray *array, Toy_Literal literal);

//TODO: add a function to get the capacity & count

#endif /* TOY_LITERAL_ARRAY_H_ */
