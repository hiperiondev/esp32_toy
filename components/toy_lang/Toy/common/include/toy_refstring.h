/**
 * @file toy_refstring.h
 * @brief @@???@@
 *
 */

#ifndef TOY_REFSTRING_H_
#define TOY_REFSTRING_H_

#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#include "toy_common.h"

//memory allocation hook
/**
 * @typedef void* (*Toy_RefStringAllocatorFn)(void *pointer, size_t oldSize, size_t newSize)
 * @brief Prototype for interface conforms to Toy's memory API, and generally shouldn't be used.
 *
 * @param pointer
 * @param oldSize
 * @param newSize
 */
typedef void* (*Toy_RefStringAllocatorFn)(void *pointer, size_t oldSize, size_t newSize);

/**
 * @fn void Toy_setRefStringAllocatorFn(Toy_RefStringAllocatorFn)
 * @brief Conforms to and is invoked by Toy's memory API, and generally shouldn't be used.
 *
 * @param Toy_RefStringAllocatorFn
 */
TOY_API void Toy_setRefStringAllocatorFn(Toy_RefStringAllocatorFn);

//the RefString structure
/**
 * @typedef Toy_RefString
 * @brief @@???@@
 *
 */
typedef struct Toy_RefString {
    size_t length; /**< @@???@@ */
    int refCount;  /**< @@???@@ */
    char data[];   /**< @@???@@ */
} Toy_RefString;

//API
/**
 * @fn Toy_RefString* Toy_createRefString(const char *cstring)
 * @brief Wraps Toy_CreateRefStringLength, by determining the length of the given cstring and passing it to the other function.
 *
 * @param cstring
 * @return
 */
TOY_API Toy_RefString* Toy_createRefString(const char *cstring);

/**
 * @fn Toy_RefString* Toy_createRefStringLength(const char *cstring, size_t length)
 * @brief Returns a new Toy_RefString, containing a copy of cstring, or NULL on error.
 *        This function also sets the returned refstring's reference counter to 1.
 *
 * @param cstring
 * @param length
 * @return
 */
TOY_API Toy_RefString* Toy_createRefStringLength(const char *cstring, size_t length);

/**
 * @fn void Toy_deleteRefString(Toy_RefString *refString)
 * @brief Reduces the refString's reference counter by 1 and, if it reaches 0, frees the memory.
 *
 * @param refString
 */
TOY_API void Toy_deleteRefString(Toy_RefString *refString);

/**
 * @fn int Toy_countRefString(Toy_RefString *refString)
 * @brief Returns the total number of references to refString, for debugging.
 *
 * @param refString
 * @return
 */
TOY_API int Toy_countRefString(Toy_RefString *refString);

/**
 * @fn size_t Toy_lengthRefString(Toy_RefString *refString)
 * @brief Returns the length of the underlying cstring of refString.
 *
 * @param refString
 * @return
 */
TOY_API size_t Toy_lengthRefString(Toy_RefString *refString);

/**
 * @fn Toy_RefString* Toy_copyRefString(Toy_RefString *refString)
 * @brief Increases the reference counter of refString by 1, before returning the given pointer.
 *
 * @param refString
 * @return
 */
TOY_API Toy_RefString* Toy_copyRefString(Toy_RefString *refString);

/**
 * @fn Toy_RefString* Toy_deepCopyRefString(Toy_RefString *refString)
 * @brief Behaves identically to Toy_copyRefString, except that it explicitly preforms a deep copy of the internal memory. Using this function should be done carefully, as it incurs a performance penalty that negates the benefit of this module.
 *
 * @param refString
 * @return
 */
TOY_API Toy_RefString* Toy_deepCopyRefString(Toy_RefString *refString);

/**
 * @fn const char* Toy_toCString(Toy_RefString *refString)
 * @brief Exposes the interal cstring of refString. Only use this function when dealing with external APIs.
 *
 * @param refString
 * @return
 */
TOY_API const char* Toy_toCString(Toy_RefString *refString);

/**
 * @fn bool Toy_equalsRefString(Toy_RefString *lhs, Toy_RefString *rhs)
 * @brief Returns true when the two refstrings are either the same refstring, or contain the same value. Otherwise it returns false.
 *
 * @param lhs
 * @param rhs
 * @return
 */
TOY_API bool Toy_equalsRefString(Toy_RefString *lhs, Toy_RefString *rhs);

/**
 * @fn bool Toy_equalsRefStringCString(Toy_RefString *lhs, char *cstring)
 * @brief Returns true when the refString contains the same value as the cstring. Otherwise it returns false.
 *
 * @param lhs
 * @param cstring
 * @return
 */
TOY_API bool Toy_equalsRefStringCString(Toy_RefString *lhs, char *cstring);

//TODO: merge refstring memory

#endif /* TOY_REFSTRING_H_ */

