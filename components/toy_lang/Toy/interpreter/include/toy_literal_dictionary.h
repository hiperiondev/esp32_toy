#ifndef TOY_LITERAL_DICTIONARY_H_
#define TOY_LITERAL_DICTIONARY_H_

#include "toy_common.h"
#include "toy_literal.h"

//TODO: benchmark this
#define TOY_DICTIONARY_MAX_LOAD 0.75

/**
 * @typedef Toy_private_dictionary_entry
 * @brief
 *
 */
typedef struct Toy_private_dictionary_entry {
    Toy_Literal key;   /**< */
    Toy_Literal value; /**< */
} Toy_private_dictionary_entry;

/**
 * @typedef Toy_LiteralDictionary
 * @brief
 *
 */
typedef struct Toy_LiteralDictionary {
    Toy_private_dictionary_entry *entries; /**< */
    int capacity; /**< */
    int count;    /**< */
    int contains; /**< */ //count + tombstones, for internal use
} Toy_LiteralDictionary;

/**
 * @fn void Toy_initLiteralDictionary(Toy_LiteralDictionary *dictionary)
 * @brief
 *
 * @param dictionary
 */
TOY_API void Toy_initLiteralDictionary(Toy_LiteralDictionary *dictionary);

/**
 * @fn void Toy_freeLiteralDictionary(Toy_LiteralDictionary *dictionary)
 * @brief
 *
 * @param dictionary
 */
TOY_API void Toy_freeLiteralDictionary(Toy_LiteralDictionary *dictionary);

/**
 * @fn void Toy_setLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key, Toy_Literal value)
 * @brief
 *
 * @param dictionary
 * @param key
 * @param value
 */
TOY_API void Toy_setLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key, Toy_Literal value);

/**
 * @fn Toy_Literal Toy_getLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key)
 * @brief
 *
 * @param dictionary
 * @param key
 * @return
 */
TOY_API Toy_Literal Toy_getLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key);

/**
 * @fn vvoid Toy_removeLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key)
 * @brief
 *
 * @param dictionary
 * @param key
 */
TOY_API void Toy_removeLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key);

/**
 * @fn bool Toy_existsLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key)
 * @brief
 *
 * @param dictionary
 * @param key
 * @return
 */
TOY_API bool Toy_existsLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key);

#endif /* TOY_LITERAL_DICTIONARY_H_ */
