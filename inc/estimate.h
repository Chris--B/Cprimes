#pragma once

#include "defines.h"

START_EXTERN_C

/*
	Estimate the number of primes below NUM.
	Lower and Upper bound functions.

	See: http://primes.utm.edu/howmany.shtml
*/
double estimatelo(double num);
double estimatehi(double num);

END_EXTERN_C
