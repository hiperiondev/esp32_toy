/**
 * @file toy_memory.h
 * @brief @@???@@
 *
 */

#ifndef TOY_MEMORY_H_
#define TOY_MEMORY_H_

#include <stddef.h>

#include "toy_common.h"

/**
 * @def TOY_GROW_CAPACITY
 * @brief calculates, in place, what size of memory should be allocated based on the previous size.
 *
 */
#define TOY_GROW_CAPACITY(capacity)                       ((capacity) < 8 ? 8 : (capacity) * 2)

/**
 * @def TOY_GROW_CAPACITY_FAST
 * @brief Calculates, in place, what size of memory should be allocated based on the previous size. It grows faster than TOY_GROW_CAPACITY.
 *
 */
#define TOY_GROW_CAPACITY_FAST(capacity)                  ((capacity) < 32 ? 32 : (capacity) * 2)

/**
 * @def TOY_ALLOCATE
 * @brief Wraps Toy_reallocate, which itself calls the allocator function. type is the type that will be allocated, and count is the number which will be needed (usually calculated with TOY_GROW_CAPACITY).
 *        returns a pointer of type.
 *
 */
#define TOY_ALLOCATE(type, count)                         ((type*)Toy_reallocate(NULL, 0, sizeof(type) * (count)))

/**
 * @def TOY_FREE
 * @brief Wraps Toy_reallocate, which itself calls the allocator function. type is the type that will be freed, and pointer is to what is being freed. This should only be used when a single element has been allocated, as opposed to an array.
 *
 */
#define TOY_FREE(type, pointer)                           Toy_reallocate(pointer, sizeof(type), 0)

/**
 * @def TOY_FREE_ARRAY
 * @brief Wraps Toy_reallocate, which itself calls the allocator function. type is the type that will be freed, pointer is a reference to what is being freed, and oldCount is the size of the array being freed. This should only be used when an array has been allocated, as opposed to a single element.
 *
 */
#define TOY_FREE_ARRAY(type, pointer, oldCount)           Toy_reallocate((type*)pointer, sizeof(type) * (oldCount), 0)

/**
 * @def TOY_GROW_ARRAY
 * @brief Wraps Toy_reallocate, which itself calls the allocator function. type is the type that is being operated on, pointer is what is being resized, oldCount is the previous size of the array and count is the new size of the array (usually calculated with TOY_GROW_CAPACITY).
 *
 */
#define TOY_GROW_ARRAY(type, pointer, oldCount, count)    (type*)Toy_reallocate((type*)pointer, sizeof(type) * (oldCount), sizeof(type) * (count))

/**
 * @def TOY_SHRINK_ARRAY
 * @brief Wraps Toy_reallocate, which itself calls the allocator function. type is the type that is being operated on, pointer is what is being resized, oldCount is the previous size of the array and count is the new size of the array.
 *        This returns a pointer of type.
 *
 */
#define TOY_SHRINK_ARRAY(type, pointer, oldCount, count)  (type*)Toy_reallocate((type*)pointer, sizeof(type) * (oldCount), sizeof(type) * (count))

//implementation details
/**
 * @fn  void* Toy_reallocate(void *pointer, size_t oldSize, size_t newSize)
 * @brief Wraps a call to the internal assigned memory allocator.
 *        This function shouldn't be called directly. Instead, use one of the given macros.
 *
 * @param pointer
 * @param oldSize
 * @param newSize
 */
TOY_API void* Toy_reallocate(void *pointer, size_t oldSize, size_t newSize);

//assign the memory allocator
/**
 * @typedef void* (*Toy_MemoryAllocatorFn)(void *pointer, size_t oldSize, size_t newSize)
 * @brief This function interface is used for defining any memory allocator functions.
 *        Any and all memory allocator functions should:
 *          - Take a pointer to a previously allocated block of memory, or NULL
 *          - Take the oldSize, which is the previous size of the pointer allocated, in bytes (oldSize can be 0)
 *          - Take the newSize, which is the new size of the buffer to be allocaated, in bytes (newSize can be 0)
 *          - Return the newly allocated buffer, or NULL if newSize is zero
 *          - Return NULL on error
 *
 * @param pointer
 * @param oldSize
 * @param newSize
 */
typedef void* (*Toy_MemoryAllocatorFn)(void *pointer, size_t oldSize, size_t newSize);

/**
 * @fn void Toy_setMemoryAllocator(Toy_MemoryAllocatorFn)
 * @brief Sets the memory allocator, replacing the default memory allocator.
 *        This function also overwrites any given refstring memory allocator, see toy_refstring.h.
 *
 * @param Toy_MemoryAllocatorFn
 */
TOY_API void Toy_setMemoryAllocator(Toy_MemoryAllocatorFn);

#endif /* TOY_MEMORY_H_ */
