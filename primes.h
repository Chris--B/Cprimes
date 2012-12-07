#ifndef CPRIMES_H
#define CPRIMES_H

#include <errno.h>
#include <inttypes.h>
#include <string.h>

#ifdef __cplusplus
	#define START_EXTERN_C extern "C" {
	#define END_EXTERN_C }
#else
	#define START_EXTERN_C
	#define END_EXTERN_C
#endif

START_EXTERN_C

enum Primality { MaybePrime, NotPrime };

//431 primes, 2 <= p <= 3001
#define CACHE_MAX 3001
#define CACHE_SIZE (sizeof cache / sizeof cache[0])
extern uint64_t cache [];

/*
	Estimate the number of primes below NUM.
	Lower and Upper bound functions.

	See: http://primes.utm.edu/howmany.shtml
*/
double estimatelo(double num);
double estimatehi(double num);

/*
	Sieve from Sieve of Eratosthenes.
	*SIEVE_P contains SIEVE_INDEX_OF(NUM) + 1 bytes of MAYBEPRIME and NOTPRIME. *SIEVE_P still needs to be parsed to produce a list of primes.

	See: http://programmingpraxis.com/2009/02/19/sieve-of-eratosthenes/
*/
int eratos_sieve(uint64_t num, uint8_t** sieve_p);

/*
	Sieves contains only odd numbers, so interfacing them can be difficult.
*/
static inline size_t sieve_index_of(uint64_t value)
{
	return (value - 1)/ 2;
}
static inline uint64_t sieve_value_at(size_t index)
{
	return (2 * index) + 1;
}

int millerrabin_round(const char* num_str, const char* d_str, uint64_t s, uint64_t witness);

END_EXTERN_C

//CPRIMES_H
#endif