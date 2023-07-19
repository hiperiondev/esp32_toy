/**
 * @file toy_common.h
 * @brief
 *
 */

#ifndef TOY_COMMON_H_
#define TOY_COMMON_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define TOY_VERSION_MAJOR 1 /**< current major version of Toy */
#define TOY_VERSION_MINOR 1 /**< current minor version of Toy */
#define TOY_VERSION_PATCH 6 /**< current patch version of Toy */

//platform/compiler-specific instructions
#if defined(__linux__) || defined(__MINGW32__) || defined(__GNUC__)

/**
 * @def TOY_API
 * @brief This definition of this macro is platform-dependant, and used to enable cross-platform compilation of shared and static libraries.
 *
 */
#define TOY_API extern

#elif defined(_MSC_VER)

#ifndef TOY_EXPORT
#define TOY_API __declspec(dllimport)
#else
#define TOY_API __declspec(dllexport)
#endif

#else

#define TOY_API extern

#endif
#endif /* TOY_COMMON_H_ */

