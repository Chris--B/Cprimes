
#include "atkin.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// stdboo.h uses int, which is 4 bytes on my machine. We only need 1 bit, to be honest.
typedef unsigned char bool;

#define FLIP(x) (x) = !(x)

size_t atkin(int max, uint32_t** results)
{
	if(max < 2) return 0;
	else if(max < 3) return 1;
	else if(max < 5) return 2;
	else if(max < 7) return 3;

	bool save_results = !!results;
	uint32_t* p = NULL;

	size_t results_len = 3;
	size_t prime_estimate  = (max/log(max)*(1 + 1.2762/log(max)) + 1);

	bool *sieve = calloc(max, sizeof(bool));
	if(!sieve)
	{
		fprintf(stderr, "Error allocating %zu bytes in Atkins Sieve for SIEVE.\n", max * sizeof(bool));
		exit(1);
	}
	for(int i = 0; i < max; i++)
	{
		switch(i % 60)
		{
			case  1: case 13: case 17: case 29:
			case 37: case 41: case 49: case 53:
				//for each solution to 4x^2 + y^2 = i
					FLIP(sieve[i]);
				break;
			case  7: case 19: case 31: case 43:
				//for each solution to 3x^2 + y^2 = i
					FLIP(sieve[i]);
				break;
			case 11: case 23: case 47: case 59:
				//for each solution to 3x^2 - y^2 = i if x > y
					FLIP(sieve[i]);
				break;
		}
	}

	if(save_results)
	{
		p = *results;
		p = malloc( prime_estimate * sizeof(uint32_t));
		if(!p)
		{
			fprintf(stderr, "Error allocating %zu bytes in Atkins Sieve for RESULTS.", prime_estimate * sizeof(uint32_t));
			exit(1);
		}
	}	
	for(int i = 0; i < max; i++)
	{
		if(sieve[i])
		{
			if(save_results)
			{
				p[results_len] = i;
			}
			results_len++;
			for(int k = i * i; k < max; k += i * i)
			{
				sieve[k] = 0;
			}
		}
	}
	return results_len;
}

