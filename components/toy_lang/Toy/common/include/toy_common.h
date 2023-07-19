#ifndef TOY_COMMON_H_
#define TOY_COMMON_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define TOY_VERSION_MAJOR 1
#define TOY_VERSION_MINOR 1
#define TOY_VERSION_PATCH 6

//platform/compiler-specific instructions
#if defined(__linux__) || defined(__MINGW32__) || defined(__GNUC__)

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

