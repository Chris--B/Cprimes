#include "eratos.h"
#include "estimate.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
	\biref Return the index of \p value in the internal sieve used by eratos()
*/
static size_t odd_array_index_of(uint64_t value) {
	return (size_t)(value - 1) / 2;
}

/**
	\biref Return the value represented by \p index in the internal sieve used by eratos()
*/
static uint64_t odd_array_value_at(size_t index) {
	return (2 * index) + 1;
}

/*
	The Sieve of Eratosthenes works by crossing off multiples of known primes to find more. It starts with an array initialized with \a MaybePrime starting with 3 (we skip evens because they're obvious) and ending with the sqrt(\a num). We go through the array and "cross off" every 3rd, and then 5th, etc. element by setting it to \a NotPrime. The next number to iterate by is the next number in the array still set to \a MaybePrime. By the time we've gotten to the end, the only elements left set as \a MaybePrime have no factors - a.k.a. they're prime.
*/
CPRIMES_DEC int eratos(uint64_t num, uint64_t** primes_array, size_t *len) {
	/* If we're not given an array to store output, don't. */
	int save_results = primes_array != 0;

	size_t primes_count = 0;
	size_t prime_estimate;
	size_t root_index;
	size_t sieve_len;
	size_t i, k;

	uint64_t *p = save_results ? *primes_array : NULL;
	uint8_t* sieve = NULL;

	if(num == 0) {
		*len = 0;
		*primes_array = NULL;
		return errno = 0;
	}

	/*
		num is the largest number in the sieve.
		If it's even, round down to the nearest odd. (aka subtract one)
	*/
	if(num % 2 != 0) {
		num--;
	}
	if(num > SIZE_MAX) {
		return errno = EFBIG;
	}

	sieve_len = odd_array_index_of(num) + 1;

	/* Index of sqrt(n) - This is when the sieving knows it can stop */
	root_index = odd_array_index_of(sqrt(num));

	/*
		http://primes.utm.edu/howmany.shtml
		Approximation for primes below N.
		Overestimates a tiny bit to avoid missing some.
	*/
	prime_estimate  = (num/log(num) * (1 + 1.2762/log(num)) + 1);

	sieve = calloc(sieve_len, sizeof (uint8_t));
	if(!sieve) {
		return errno = ENOMEM;
	}

	if(save_results) {
		p = malloc(prime_estimate * sizeof(uint64_t));
		if (!p) {
			free(sieve);
			return errno = ENOMEM;
		}
	}
	for(i = 1; i <= root_index; i++) {
		if (sieve[i] == MaybePrime) {
			for(k = i + (size_t)odd_array_value_at(i); k < sieve_len; k += (size_t)odd_array_value_at(i)) {
				sieve[k] = NotPrime;	/* "crossed off" */
			}
		}
	}

	for(i = 0; i < sieve_len; i++) {
		if (!sieve[i]) {
			if(save_results) {
				p[primes_count] = odd_array_value_at(i);
			}
			primes_count++;
		}
	}
	if(save_results) {
		/*
			2 is prime, but isn't in our sieve as it's even.
			1, however, is odd but not prime: It's a unit.
			We get two birds with one stone here.
		*/
		p[0] = 2;
		p[primes_count] = 0;
		p = realloc(p, sizeof(p[0]) * (primes_count + 1));
		*primes_array = p;
	}

	free(sieve);
	if(len) {
		*len =  primes_count;
	}
	return errno = 0;
}
