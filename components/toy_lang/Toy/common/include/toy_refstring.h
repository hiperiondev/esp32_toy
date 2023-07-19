#ifndef TOY_REFSTRING_H_
#define TOY_REFSTRING_H_

#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#include "toy_common.h"

//memory allocation hook
/**
 * @typedef void* (*Toy_RefStringAllocatorFn)(void *pointer, size_t oldSize, size_t newSize)
 * @brief
 *
 * @param pointer
 * @param oldSize
 * @param newSize
 */
typedef void* (*Toy_RefStringAllocatorFn)(void *pointer, size_t oldSize, size_t newSize);

/**
 * @fn void Toy_setRefStringAllocatorFn(Toy_RefStringAllocatorFn)
 * @brief
 *
 * @param
 */
TOY_API void Toy_setRefStringAllocatorFn(Toy_RefStringAllocatorFn);

//the RefString structure
/**
 * @struct Toy_RefString
 * @brief
 *
 */
typedef struct Toy_RefString {
    size_t length; /**< */
    int refCount;  /**< */
    char data[];   /**< */
} Toy_RefString;

//API
/**
 * @fn Toy_RefString* Toy_createRefString(const char *cstring)
 * @brief
 *
 * @param cstring
 * @return
 */
TOY_API Toy_RefString* Toy_createRefString(const char *cstring);

/**
 * @fn Toy_RefString* Toy_createRefStringLength(const char *cstring, size_t length)
 * @brief
 *
 * @param cstring
 * @param length
 * @return
 */
TOY_API Toy_RefString* Toy_createRefStringLength(const char *cstring, size_t length);

/**
 * @fn void Toy_deleteRefString(Toy_RefString *refString)
 * @brief
 *
 * @param refString
 */
TOY_API void Toy_deleteRefString(Toy_RefString *refString);

/**
 * @fn int Toy_countRefString(Toy_RefString *refString)
 * @brief
 *
 * @param refString
 * @return
 */
TOY_API int Toy_countRefString(Toy_RefString *refString);

/**
 * @fn size_t Toy_lengthRefString(Toy_RefString *refString)
 * @brief
 *
 * @param refString
 * @return
 */
TOY_API size_t Toy_lengthRefString(Toy_RefString *refString);

/**
 * @fn Toy_RefString* Toy_copyRefString(Toy_RefString *refString)
 * @brief
 *
 * @param refString
 * @return
 */
TOY_API Toy_RefString* Toy_copyRefString(Toy_RefString *refString);

/**
 * @fn Toy_RefString* Toy_deepCopyRefString(Toy_RefString *refString)
 * @brief
 *
 * @param refString
 * @return
 */
TOY_API Toy_RefString* Toy_deepCopyRefString(Toy_RefString *refString);

/**
 * @fn const char* Toy_toCString(Toy_RefString *refString)
 * @brief
 *
 * @param refString
 * @return
 */
TOY_API const char* Toy_toCString(Toy_RefString *refString);

/**
 * @fn bool Toy_equalsRefString(Toy_RefString *lhs, Toy_RefString *rhs)
 * @brief
 *
 * @param lhs
 * @param rhs
 * @return
 */
TOY_API bool Toy_equalsRefString(Toy_RefString *lhs, Toy_RefString *rhs);

/**
 * @fn bool Toy_equalsRefStringCString(Toy_RefString *lhs, char *cstring)
 * @brief
 *
 * @param lhs
 * @param cstring
 * @return
 */
TOY_API bool Toy_equalsRefStringCString(Toy_RefString *lhs, char *cstring);

//TODO: merge refstring memory

#endif /* TOY_REFSTRING_H_ */

