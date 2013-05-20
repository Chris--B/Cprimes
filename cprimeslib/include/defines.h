#pragma once

#ifdef __cplusplus
#	define EXTERN_C extern "C"
#else
#	define EXTERN_C extern
#endif

// does this cover 64-bit windows?
#ifdef _WIN32
#	ifdef MAKINGDLL
#		define Cprimes_Public EXTERN_C __declspec(dllexport)
#		define Cprimes_Private static
#	else
#		define Cprimes_Public EXTERN_C __declspec(dllimport)
#		define Cprimes_Private static
#	endif
#else
#	define Cprimes_Public EXTERN_C
#	define Cprimes_Private static
#endif

/** @brief Expand into the size of an array with compile-time known size
*/
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

//iffy on naming, so I won't change this yet
#define CPRIMES_DEC Cprimes_Public
#define START_EXTERN_C
#define END_EXTERN_C


// EVERYTHING uses these, but they're not as portable as they should be.
// Putting them here might save some headache down the road.
#include <stdint.h>
#include <inttypes.h>

#ifdef WIN32 // <__<
#define snprintf _snprintf
#define PRIu64 "I64u"
#endif
