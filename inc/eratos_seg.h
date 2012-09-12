#ifndef ERATOS_SEG
#define ERATOS_SEG

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stddef.h>

/*
	return number of primers less than n,
	stored in *OUT

	Assumes unallocated *OUT

	Pass NULL to not store result, but instead just
	return number of primes
*/
size_t eratos_seg(int n, uint64_t **out);

#ifdef __cplusplus
}
#endif

#endif //ERATOS_SEG
