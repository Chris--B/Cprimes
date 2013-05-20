#pragma once

#ifdef __cplusplus
#	define EXTERN_C extern "C"
#else
#	define EXTERN_C extern
#endif

#define START_EXTERN_C
#define END_EXTERN_C


/** @brief Expand into the size of an array with compile-time known size
*/
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/*
	Fixed width-int types are used all over the project, put stuff here just incase we need to do some tinkering.
*/
#include <inttypes.h>

#ifdef WIN32
	#include <windows-defines.h>
#else
	#define Cprimes_Public EXTERN_C
	#define Cprimes_Private static
#endif

/* iffy on naming, so I won't change this yet */
#define CPRIMES_DEC Cprimes_Public
