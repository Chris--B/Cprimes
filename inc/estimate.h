#pragma once

#include "defines.h"

START_EXTERN_C

/*
	Estimate the number of primes below NUM.
	Lower and Upper bound functions.

	See: http://primes.utm.edu/howmany.shtml
*/
CPRIMES_DEC double estimatelo(double num);
CPRIMES_DEC double estimatehi(double num);

END_EXTERN_C
