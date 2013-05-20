#pragma once

/*
	Windows does a lot of things differently. This header exists to smooth those differences out.
*/

/* No/limited C99 */
#define snprintf _snprintf
#define PRIu64 "I64u"

#ifdef MAKINGDLL
	#define Cprimes_Public EXTERN_C __declspec(dllexport)
	#define Cprimes_Private static
#else
	#define Cprimes_Public EXTERN_C __declspec(dllimport)
	#define Cprimes_Private static
#endif

/*
	Some of Microsoft's errors are silly. This disables them.
*/
/* Warns about implicit conversions between integer and floating types */
#pragma warning (disable: 4244)
