#pragma once

#ifdef __cplusplus
	#define START_EXTERN_C extern "C" {
	#define END_EXTERN_C }
#else
	#define START_EXTERN_C
	#define END_EXTERN_C
#endif

#include <inttypes.h>
