/**
 * @file toy_reffunction.h
 * @brief @@???@@
 *
 */

#ifndef TOY_REFFUNCTION_H_
#define TOY_REFFUNCTION_H_

#include <stddef.h>

#include "toy_common.h"

//memory allocation hook
/**
 * @fn void* (*Toy_RefFunctionAllocatorFn)(void *pointer, size_t oldSize, size_t newSize)
 * @brief @@???@@
 *
 * @param pointer
 * @param oldSize
 * @param newSize
 */
typedef void* (*Toy_RefFunctionAllocatorFn)(void *pointer, size_t oldSize, size_t newSize);

/**
 * @fn void Toy_setRefFunctionAllocatorFn(Toy_RefFunctionAllocatorFn)
 * @brief Conforms to and is invoked by Toy's memory API, and generally shouldn't be used.
 *
 * @param Toy_RefFunctionAllocatorFn
 */
TOY_API void Toy_setRefFunctionAllocatorFn(Toy_RefFunctionAllocatorFn);

//the RefFunction structure
/**
 * @typedef Toy_RefFunction
 * @brief @@???@@
 *
 */
typedef struct Toy_RefFunction {
    size_t length;        /**< @@???@@ */
    int refCount;         /**< @@???@@ */
    unsigned char data[]; /**< @@???@@ */
} Toy_RefFunction;

//API
/**
 * @fn Toy_RefFunction* Toy_createRefFunction(const void *data, size_t length)
 * @brief Returns a new Toy_RefFunction, containing a copy of data, or NULL on error.
 *        This function also sets the returned refFunction's reference counter to 1.
 *
 * @param data
 * @param length
 * @return
 */
TOY_API Toy_RefFunction* Toy_createRefFunction(const void *data, size_t length);

/**
 * @fn void Toy_deleteRefFunction(Toy_RefFunction *refFunction)
 * @brief Reduces the refFunction's reference counter by 1 and, if it reaches 0, frees the memory.
 *
 * @param refFunction
 */
TOY_API void Toy_deleteRefFunction(Toy_RefFunction *refFunction);

/**
 * @fn int Toy_countRefFunction(Toy_RefFunction *refFunction)
 * @brief Returns the total number of references to refFunction, for debugging.
 *
 * @param refFunction
 * @return
 */
TOY_API int Toy_countRefFunction(Toy_RefFunction *refFunction);

/**
 * @fn size_t Toy_lengthRefFunction(Toy_RefFunction *refFunction)
 * @brief Returns the length of the underlying bytecode of refFunction.
 *
 * @param refFunction
 * @return
 */
TOY_API size_t Toy_lengthRefFunction(Toy_RefFunction *refFunction);

/**
 * @fn Toy_RefFunction* Toy_copyRefFunction(Toy_RefFunction *refFunction)
 * @brief Increases the reference counter of refFunction by 1, before returning the given pointer.
 *
 * @param refFunction
 * @return
 */
TOY_API Toy_RefFunction* Toy_copyRefFunction(Toy_RefFunction *refFunction);

/**
 * @fn Toy_RefFunction* Toy_deepCopyRefFunction(Toy_RefFunction *refFunction)
 * @brief Behaves identically to Toy_copyRefFunction, except that it explicitly preforms a deep copy of the internal memory. Using this function should be done carefully, as it incurs a performance penalty that negates the benefit of this module.
 *
 * @param refFunction
 * @return
 */
TOY_API Toy_RefFunction* Toy_deepCopyRefFunction(Toy_RefFunction *refFunction);

#endif /* TOY_REFFUNCTION_H_ */

