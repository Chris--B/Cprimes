#pragma once

#include <cprimes_platform.h>

#include <inttypes.h>
/* #include <stdlib.h> */

#ifdef __cplusplus
extern "C" {
#endif

/*
	Redesign this!
*/

/** @file
	@brief Functions for estimating the number of primes in an interval.

	There are three prefixes (low, high, good) on the functions. low_* will always be smaller than the actual number. high_* will always be larger. good_ will attempt to minimize error, but makes no guarantees about being larger or smaller. low <= good <= high, always.

	_estimate functions return size_t values, and should not be used if you expect the number to exceed the maximum address size of your system.

*/

/** @brief Lower bound on the number of primes <= @p num
*/
CPRIMES_EXPORT size_t low_estimate(uint64_t num);

/** @brief Upper bound on the number of primes <= @p num
*/
CPRIMES_EXPORT size_t high_estimate(uint64_t num);

/** @brief Better approximation for primes <= @p num.

	This function produces a much better estimate, but it is not
	consistently an over or lower estimate.
*/
CPRIMES_EXPORT size_t good_estimate(uint64_t num);

#ifdef __cplusplus
}
#endif
