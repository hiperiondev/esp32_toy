#ifndef TOY_MEMORY_H_
#define TOY_MEMORY_H_

#include <stddef.h>

#include "toy_common.h"

#define TOY_GROW_CAPACITY(capacity)                       ((capacity) < 8 ? 8 : (capacity) * 2)
#define TOY_GROW_CAPACITY_FAST(capacity)                  ((capacity) < 32 ? 32 : (capacity) * 2)

#define TOY_ALLOCATE(type, count)                         ((type*)Toy_reallocate(NULL, 0, sizeof(type) * (count)))

#define TOY_FREE(type, pointer)                           Toy_reallocate(pointer, sizeof(type), 0)
#define TOY_FREE_ARRAY(type, pointer, oldCount)           Toy_reallocate((type*)pointer, sizeof(type) * (oldCount), 0)

#define TOY_GROW_ARRAY(type, pointer, oldCount, count)    (type*)Toy_reallocate((type*)pointer, sizeof(type) * (oldCount), sizeof(type) * (count))
#define TOY_SHRINK_ARRAY(type, pointer, oldCount, count)  (type*)Toy_reallocate((type*)pointer, sizeof(type) * (oldCount), sizeof(type) * (count))

//implementation details
/**
 * @fn  void* Toy_reallocate(void *pointer, size_t oldSize, size_t newSize)
 * @brief
 *
 * @param pointer
 * @param oldSize
 * @param newSize
 */
TOY_API void* Toy_reallocate(void *pointer, size_t oldSize, size_t newSize);

//assign the memory allocator
/**
 * @typedef void* (*Toy_MemoryAllocatorFn)(void *pointer, size_t oldSize, size_t newSize)
 * @brief
 *
 * @param pointer
 * @param oldSize
 * @param newSize
 */
typedef void* (*Toy_MemoryAllocatorFn)(void *pointer, size_t oldSize, size_t newSize);

/**
 * @fn void Toy_setMemoryAllocator(Toy_MemoryAllocatorFn)
 * @brief
 *
 * @param
 */
TOY_API void Toy_setMemoryAllocator(Toy_MemoryAllocatorFn);

#endif /* TOY_MEMORY_H_ */
