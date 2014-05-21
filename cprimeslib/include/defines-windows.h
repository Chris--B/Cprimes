#pragma once

/*
	Windows does a lot of things differently. This header exists to smooth those differences out.
*/

/* snprintf() is really, really useful. */
#define snprintf _snprintf

/* DLLs on Windows are odd. */
#ifdef MAKINGDLL
	#define Cprimes_Public EXTERN_C __declspec(dllimport)
	#define Cprimes_Private static
#else
	#define Cprimes_Public EXTERN_C __declspec(dllexport)
	#define Cprimes_Private static
#endif
