#ifndef TOY_REFFUNCTION_H_
#define TOY_REFFUNCTION_H_

#include <stddef.h>

#include "toy_common.h"

//memory allocation hook
/**
 * @fn void* (*Toy_RefFunctionAllocatorFn)(void *pointer, size_t oldSize, size_t newSize)
 * @brief
 *
 * @param pointer
 * @param oldSize
 * @param newSize
 */
typedef void* (*Toy_RefFunctionAllocatorFn)(void *pointer, size_t oldSize, size_t newSize);

/**
 * @fn void Toy_setRefFunctionAllocatorFn(Toy_RefFunctionAllocatorFn)
 * @brief
 *
 * @param
 */
TOY_API void Toy_setRefFunctionAllocatorFn(Toy_RefFunctionAllocatorFn);

//the RefFunction structure
/**
 * @typedef Toy_RefFunction
 * @brief
 *
 */
typedef struct Toy_RefFunction {
    size_t length;        /**< */
    int refCount;         /**< */
    unsigned char data[]; /**< */
} Toy_RefFunction;

//API
/**
 * @fn Toy_RefFunction* Toy_createRefFunction(const void *data, size_t length)
 * @brief
 *
 * @param data
 * @param length
 * @return
 */
TOY_API Toy_RefFunction* Toy_createRefFunction(const void *data, size_t length);

/**
 * @fn void Toy_deleteRefFunction(Toy_RefFunction *refFunction)
 * @brief
 *
 * @param refFunction
 */
TOY_API void Toy_deleteRefFunction(Toy_RefFunction *refFunction);

/**
 * @fn int Toy_countRefFunction(Toy_RefFunction *refFunction)
 * @brief
 *
 * @param refFunction
 * @return
 */
TOY_API int Toy_countRefFunction(Toy_RefFunction *refFunction);

/**
 * @fn size_t Toy_lengthRefFunction(Toy_RefFunction *refFunction)
 * @brief
 *
 * @param refFunction
 * @return
 */
TOY_API size_t Toy_lengthRefFunction(Toy_RefFunction *refFunction);

/**
 * @fn Toy_RefFunction* Toy_copyRefFunction(Toy_RefFunction *refFunction)
 * @brief
 *
 * @param refFunction
 * @return
 */
TOY_API Toy_RefFunction* Toy_copyRefFunction(Toy_RefFunction *refFunction);

/**
 * @fn Toy_RefFunction* Toy_deepCopyRefFunction(Toy_RefFunction *refFunction)
 * @brief
 *
 * @param refFunction
 * @return
 */
TOY_API Toy_RefFunction* Toy_deepCopyRefFunction(Toy_RefFunction *refFunction);

#endif /* TOY_REFFUNCTION_H_ */

