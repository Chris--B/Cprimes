#pragma once

#include <cprimes_platform.h>

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
	Functionally equivilent to true and false.
*/
enum Primality { MaybePrime, NotPrime };

/**
	@brief Find all positive real primes below @p num. Allocate and store them in @p *primes_array, saving the number found in @p *len.

	This function uses Sieve of Eratosthenes to find primes. If @p
	primes_array is non-NULL, they are stored in an allocated buffer whose
	address is passed in. The number of primes found is stored in @p *len,
	unless @p len is NULL. This prevents undefined behavior, but calling the function without saving the length isn't very useful.

	When @p num is 0, @p *len is set to 0, @p *primes_array is set to NULL, and 0 is returned.

	@param num The upper limit on primes to find
	@param primes_array Address of array in-which to store primes found. When
	NULL, no primes are saved.
	@param len Address of variable to save number of primes found. When NULL, the number found is not saved.

	@returns Sets @p errno appropriately and returns it. When no error occurs,
	errno is set to 0 and returned.

	Example usage:
	@code{.c}
		uint64_t *primes = NULL;
		size_t count;
		size_t i;
		int err;

		err = eratos(30, &primes, &count);
		if (err) {
			fprintf(stderr, "%s", strerror(err));
			exit(1);
		}

		printf("%zu primes < 30:\n", count);
		for(i = 0; i < count; ++i) {
			printf("%"PRIu64" ", primes[i]);
		}
	@endcode
	Prints
	@code{.txt}
		10 primes < 30:
		2 3 5 7 11 13 17 19 23 29
	@endcode

	For more information on the details of the algorithm, see [this blog post](
	http://programmingpraxis.com/2009/02/19/sieve-of-eratosthenes/).

	@warning This function can allocate extremely large blocks of memory when
	@p num is large. On a machine with 8 GiB of RAM, values of @p num above
	about  1 billion cause memory errors. Use the return value or errno to
	check for errors when you think this might be a risk.

	@todo - Reference proper acedemic papers, instead of a blog post for
	describing Sieve of Eratosthenes
	- Depreciate in favor of Segmented Sieve of Eratosthenes (Unfinished!)
*/
CPRIMES_EXPORT int eratos(uint64_t num, uint64_t **primes_array, size_t *len);

#ifdef __cplusplus
}
#endif
