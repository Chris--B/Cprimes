#pragma once

#include "defines.h"

START_EXTERN_C

/*
	Redesign this!
*/
#if 0
/** @file
	@brief Functions for estimating the number of primes in an interval.

	For more information on the algorithms, see [this site]
	(http://primes.utm.edu/howmany.shtml).
*/

/** @brief Lower bound on the number of primes <= @p num
*/
CPRIMES_DEC uint64_t low_estimate(uint64_t num);

/** @brief Upper bound on the number of primes <= @p num
*/
CPRIMES_DEC uint64_t high_estimate(uint64_t num);

/** @brief Better approximation for primes <= @p num.

	This function produces a much better estimate, but it is not
	consistently an over or lower estimate. Use this if you just want a good
	 estimate, but @p num is too large to use eratos() directly.
*/
CPRIMES_DEC uint64_t good_estimate(uint64_t num);
#endif

END_EXTERN_C
