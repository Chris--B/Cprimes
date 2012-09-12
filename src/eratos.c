#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "eratos.h"

/* 
	Internal array used for sieving excludes even numbers.
	ODD_ARRAY_INDEX_OF() and ODD_ARRAY_VALUE_AT() make dealing
	with it easier.
*/
static inline size_t odd_array_index_of(uint64_t value)
{
	return (value - 1) / 2;
}
static inline uint64_t odd_array_value_at(size_t index)
{
	return (2 * index) + 1;
}

size_t eratos(int n, uint64_t** primes_array)
{
	// If we're not given an array to store output, don't.
	bool not_null_array = !!primes_array;

	/*	N is the largest number in the sieve. 
		If it's even, round down to the nearest odd. (aka subtract one)
	*/
	if (!(n & 1))
	{
		n--;
	}

	// Make our lives a little easier.
	uint64_t *p = not_null_array ? *primes_array : NULL; // Why do I not need this for O2 / O3?

	size_t primes_count  = 0;
	size_t sieve_len     = odd_array_index_of(n) + 1;

	// Index of SQRT(n) - This is when the sieving knows it can stop
	size_t root_index    = odd_array_index_of((size_t)sqrt((double)(n)));

	/* http://primes.utm.edu/howmany.shtml
	   Approximation for primes below N. 
	   Overestimates a tiny bit to avoid missing some.
	   */
	size_t prime_estimate  = (n/log(n)*(1 + 1.2762/log(n)) + 1);

	//0 = maybe prime, 1 = crossed off
	uint8_t* sieve = calloc(sieve_len, sizeof (uint8_t));
	if (!sieve)
	{
		fprintf(stderr, "Error allocating sieve of %zu bytes.\n", sieve_len * sizeof(uint8_t));
		return 0;
	}

	if(not_null_array)
	{
		if (!(p = malloc(prime_estimate * sizeof(uint64_t))))
		{
			fprintf(stderr, "Error allocating primes_array array of %zu bytes.\n",
				prime_estimate * sizeof(uint64_t));
			free(sieve);
			return 0;
		}
	}
	for(size_t i = 1; i <= root_index; i++)
	{
		if (!sieve[i])
		{
			for(size_t k = i + odd_array_value_at(i); k < sieve_len; k += odd_array_value_at(i))
			{
				sieve[k] = 1;	//"crossed off"
			}
		}
	}
	
	for(size_t i = 0; i < sieve_len; i++)
	{
		if (!sieve[i])
		{
			if(not_null_array)
			{
				p[primes_count] = odd_array_value_at(i);
			}
			primes_count++;
		}
	}
	if(not_null_array)
	{
		p[0] = 2;	// 2 is prime, but 1 is not. It's a 'unit'
		*primes_array = p;
	}

	free(sieve);
	return primes_count;
}
