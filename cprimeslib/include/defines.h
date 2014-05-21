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

#ifdef _MSC_VER
	#include <defines-windows.h>
#else
	#define Cprimes_Public EXTERN_C
	#define Cprimes_Private static
	/*
		We use this extensively for its buffer-protection,
			but we run into problems using it on windows.

		In windows-defines.h, we just use _snprintf. But off of Windows,
			we need to include / declare this properly.
	*/
	int snprintf(char*, int, const char*, ...);
#endif

/* iffy on naming, so I won't change this yet */
#define CPRIMES_DEC Cprimes_Public

#include <assert.h>
/* TODO: static_assert */

