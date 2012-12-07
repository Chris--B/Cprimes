#include "primes.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int eratos_sieve(uint64_t num, uint8_t** sieve_p)
{
	if(num > SIZE_MAX)
	{
		return errno = EFBIG;
	}
	size_t sieve_len = sieve_index_of(num) + 1;
	size_t root_index = sieve_index_of(sqrt(num) + 1);

	uint8_t* sieve = calloc(sieve_len, sizeof (uint8_t));
	*sieve_p = sieve;
	if (!sieve)
	{
		return errno = ENOMEM;
	}

	size_t i, k;
	for(i = 1; i <= root_index; i++)
	{
		if (sieve[i] == MaybePrime)
		{
			for(k = i + sieve_value_at(i); k < sieve_len; k += sieve_value_at(i))
			{
				sieve[k] = NotPrime;
			}
		}
	}
	return errno = 0;
}

