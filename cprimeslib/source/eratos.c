#include <cprimes.h>

#include "util.h"

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
	Functionally equivilent to true and false, but easier to read
*/
enum Primality {
	MaybePrime = 0,
	NotPrime   = 1
};

/**
	\brief Return the index of \p value in the internal sieve used by eratos()
*/
static size_t odd_array_index_of(uint64_t value) {
	return (value - 1) / 2;
}

/**
	\brief Return the value represented by \p index in the internal sieve used
	by eratos()
*/
static uint64_t odd_array_value_at(size_t index) {
	return (2 * index) + 1;
}

/*
	The Sieve of Eratosthenes works by crossing off multiples of known primes
	to find more. It starts with an array initialized with \a MaybePrime
	starting with 3 (we skip evens because they're obvious) and ending with
	the sqrt(\a num). We go through the array and "cross off" every 3rd, and
	then 5th, etc. element by setting it to \a NotPrime. The next number to
	iterate by is the next number in the array still set to \a MaybePrime.
	By the time we've gotten to the end, the only elements left set as
	\a MaybePrime have no factors besides themselves, a.k.a. they're prime.
*/
CPRIMES_EXPORT int eratos(uint64_t num, uint64_t** primes_array, size_t *len) {
	/* If we're not given an array to store output, don't. */
	int save_results = primes_array != NULL;

	size_t primes_count = 0;
	size_t root_index;
	size_t sieve_len;
	size_t i, k;

	uint64_t *results = save_results ? *primes_array : NULL;
	uint8_t* sieve = NULL;

	/*
		There are no primes < 2, so we return an empty array. By "empty",
		we mean a single element and length of 0.
	*/
	if(num < 2) {
		*len = 0;
		*primes_array = malloc(sizeof(results[0]));
		return errno = 0;
	}

	/*
		num is the largest number in the sieve.
		If it's even, round down to the nearest odd.
	*/
	if(num % 2 != 0) {
		num -= 1;
	}

	/*
		The size of out sieve is limited by the addressing range, which size_t
		can always hold. If num is too big, we'll run out of memory!
		(This is a job for the segmented sieve!)
	*/
	if((num / 2) > SIZE_MAX) {
		return errno = EFBIG;
	}

	sieve_len = odd_array_index_of(num) + 1;

	/* Index of sqrt(n) - This is when the sieving knows it can stop */
	root_index = odd_array_index_of((uint64_t)sqrt((double)num));

	sieve = calloc(sieve_len, sizeof (uint8_t));
	if(!sieve) {
		return errno = ENOMEM;
	}

	if(save_results) {
		/*
			Over estimate how many primes there are, we can trim off extra
			memory later. Add one to the estimate for the trailing 0.
		*/
		results = malloc((1 + high_estimate(num)) * sizeof(uint64_t));
		if (!results) {
			free(sieve);
			return errno = ENOMEM;
		}
	}

	for(i = 1; i <= root_index; i += 1) {
		if (sieve[i] == MaybePrime) {
			for(k = i + odd_array_value_at(i);
				k < sieve_len;
				k += odd_array_value_at(i))
			{
				sieve[k] = NotPrime;	/* "crossed off" */
			}
		}
	}

	for(i = 0; i < sieve_len; i += 1) {
		if (!sieve[i]) {
			if(save_results) {
				results[primes_count] = odd_array_value_at(i);
			}
			primes_count++;
		}
	}

	if(save_results) {
		/*
			2 is prime, but isn't in our sieve because it's even.
			1, however, is odd but not prime! It's a unit.
			We get two birds with one stone here.
		*/
		results[0] = 2;
		results[primes_count] = 0;
		/* Trim the fat */
		results = realloc(results, sizeof(results[0]) * (primes_count + 1));
		*primes_array = results;
	}

	free(sieve);
	if(len) {
		*len =  primes_count;
	}
	return errno = 0;
}

#ifdef __cplusplus
extern "C" {
#endif
