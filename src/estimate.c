#include "estimate.h"

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

CPRIMES_DEC double estimatelo(double num) {
	return num;
}
CPRIMES_DEC double estimatehi(double num) {
	return (num / log(num) * (1 + 1.2762 / log(num)) + 1);
}

#ifdef __cplusplus
}
#endif