#pragma once

/** @brief Expand into the size of an array with compile-time known size
*/
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/* TODO: static_assert */

#if _WIN32
	#ifndef _CRT_SECURE_NO_WARNINGS
		#define _CRT_SECURE_NO_WARNINGS
	#endif
#endif
