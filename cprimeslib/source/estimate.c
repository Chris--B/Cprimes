#include "estimate.h"

#include <math.h>

START_EXTERN_C

CPRIMES_DEC uint64_t low_estimate(uint64_t num) {
	(void)num;
	return 0;
}

CPRIMES_DEC uint64_t high_estimate(uint64_t num) {
	return (num / log(num) * (1 + 1.2762 / log(num)) + 1);
}

CPRIMES_DEC uint64_t good_estimate(uint64_t num) {
	(void)num;
	return 0;
}

END_EXTERN_C