#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "eratos.h"
#include "estimate.h"

/* 
	Internal array used for sieving excludes even numbers.
	ODD_ARRAY_INDEX_OF() and ODD_ARRAY_VALUE_AT() make dealing
	with it easier.
*/
static inline size_t odd_array_index_of(uint64_t value) {
	return (value - 1) / 2;
}
static inline uint64_t odd_array_value_at(size_t index) {
	return (2 * index) + 1;
}

int eratos(uint64_t num, uint64_t** primes_array, size_t *len) {
	// If we're not given an array to store output, don't.
	int not_null_array = !!primes_array;

	/*	
		N is the largest number in the sieve. 
		If it's even, round down to the nearest odd. (aka subtract one)
	*/
	if(num % 2 != 0) {
		num--;
	}
	if(num > SIZE_MAX) {
		return errno = EFBIG;
	}


	size_t i, k;

	uint64_t *p = not_null_array ? *primes_array : NULL;

	size_t primes_count  = 0;
	size_t sieve_len     = odd_array_index_of(num) + 1;

	// Index of SQRT(n) - This is when the sieving knows it can stop
	size_t root_index    = odd_array_index_of(sqrt(num));

	/*
		http://primes.utm.edu/howmany.shtml
		Approximation for primes below N. 
		Overestimates a tiny bit to avoid missing some.
	*/
	size_t prime_estimate  = (num/log(num)*(1 + 1.2762/log(num)) + 1);

	uint8_t* sieve = calloc(sieve_len, sizeof (uint8_t));
	if(!sieve) {
		fprintf(stderr, "Error allocating sieve of %lu bytes.\n", (unsigned long)(sieve_len * sizeof(uint8_t)));
		return errno = ENOMEM;
	}

	if(not_null_array) {
		if (!(p = malloc(prime_estimate * sizeof(uint64_t)))) {
			fprintf(stderr, "Error allocating primes_array array of %lu bytes.\n",
				(unsigned long)(prime_estimate * sizeof(uint64_t)));
			free(sieve);
			return errno = ENOMEM;
		}
	}
	for(i = 1; i <= root_index; i++) {
		if (sieve[i] == MaybePrime) {
			for(k = i + odd_array_value_at(i); k < sieve_len; k += odd_array_value_at(i)) {
				sieve[k] = NotPrime;	//"crossed off"
			}
		}
	}
	
	for(i = 0; i < sieve_len; i++) {
		if (!sieve[i]) {
			if(not_null_array) {
				p[primes_count] = odd_array_value_at(i);
			}
			primes_count++;
		}
	}
	if(not_null_array) {
		p[0] = 2;	// 2 is prime, but 1 is not. It's a 'unit'
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
