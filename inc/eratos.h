#pragma once

#include "defines.h"

#include <errno.h>
#include <stdlib.h>

START_EXTERN_C

enum Primality { MaybePrime, NotPrime };

/*
	Sieve from Sieve of Eratosthenes.
	*SIEVE_P contains SIEVE_INDEX_OF(NUM) + 1 bytes of MAYBEPRIME and NOTPRIME. *SIEVE_P still needs to be parsed to produce a list of primes.

	See: http://programmingpraxis.com/2009/02/19/sieve-of-eratosthenes/
*/
int eratos(uint64_t num, uint64_t** primes_array, size_t *len);

END_EXTERN_C

