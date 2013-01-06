#pragma once

#ifdef __cplusplus
	#define START_EXTERN_C extern "C" {
	#define END_EXTERN_C }
#else
	#define START_EXTERN_C
	#define END_EXTERN_C
#endif

#ifndef MAKINGDLL
	#define CPRIMES_DEC __declspec(dllimport)
#else
	#define CPRIMES_DEC __declspec(dllexport)
#endif

//Everything uses it, move it out here to make life easier if we have decide to change it.
#include <inttypes.h>
