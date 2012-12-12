#pragma once

#include "defines.h"

#include <errno.h>

START_EXTERN_C

enum Primality { MaybePrime, NotPrime };

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

END_EXTERN_C
