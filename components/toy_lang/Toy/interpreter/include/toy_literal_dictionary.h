/**
 * @file toy_literal_dictionary.h
 * @brief @@???@@
 *
 */

#ifndef TOY_LITERAL_DICTIONARY_H_
#define TOY_LITERAL_DICTIONARY_H_

#include "toy_common.h"
#include "toy_literal.h"

//TODO: benchmark this
#define TOY_DICTIONARY_MAX_LOAD 0.75

/**
 * @typedef Toy_private_dictionary_entry
 * @brief @@???@@
 *
 */
typedef struct Toy_private_dictionary_entry {
    Toy_Literal key;   /**< @@???@@ */
    Toy_Literal value; /**< @@???@@ */
} Toy_private_dictionary_entry;

/**
 * @typedef Toy_LiteralDictionary
 * @brief @@???@@
 *
 */
typedef struct Toy_LiteralDictionary {
    Toy_private_dictionary_entry *entries; /**< @@???@@ */
    int capacity; /**< @@???@@ */
    int count;    /**< @@???@@ */
    int contains; /**< count + tombstones, for internal use */
} Toy_LiteralDictionary;

/**
 * @fn void Toy_initLiteralDictionary(Toy_LiteralDictionary *dictionary)
 * @brief Initializes the Toy_LiteralDictionary pointed to by dictionary.
 *
 * @param dictionary
 */
TOY_API void Toy_initLiteralDictionary(Toy_LiteralDictionary *dictionary);

/**
 * @fn void Toy_freeLiteralDictionary(Toy_LiteralDictionary *dictionary)
 * @brief Frees a Toy_LiteralDictionary pointed to by dictionary. Every literal within is passed to Toy_freeLiteral before its memory is released.
 *
 * @param dictionary
 */
TOY_API void Toy_freeLiteralDictionary(Toy_LiteralDictionary *dictionary);

/**
 * @fn void Toy_setLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key, Toy_Literal value)
 * @brief Inserts the given key-value pair of literals into dictionary, creating it if it doesn't exist, or freeing and overwriting it if key is already present. This function may also expand the memory buffer if needed.
 *        Literal functions and opaques cannot be used as keys.
 *
 * @param dictionary
 * @param key
 * @param value
 */
TOY_API void Toy_setLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key, Toy_Literal value);

/**
 * @fn Toy_Literal Toy_getLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key)
 * @brief Returns the value of the literal within dictionary identified by key, or a null literal if it doesn't exist.
 *        Literal functions and opaques cannot be used as keys.
 *
 * @param dictionary
 * @param key
 * @return
 */
TOY_API Toy_Literal Toy_getLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key);

/**
 * @fn vvoid Toy_removeLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key)
 * @brief Removes the key-value pair of literals from dictionary identified by key, if it exists.
 *        Literal functions and opaques cannot be used as keys.
 *
 * @param dictionary
 * @param key
 */
TOY_API void Toy_removeLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key);

/**
 * @fn bool Toy_existsLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key)
 * @brief Returns true if the key-value pair identified by key exists within dictionary, otherwise it returns false.
 *
 * @param dictionary
 * @param key
 * @return
 */
TOY_API bool Toy_existsLiteralDictionary(Toy_LiteralDictionary *dictionary, Toy_Literal key);

#endif /* TOY_LITERAL_DICTIONARY_H_ */
