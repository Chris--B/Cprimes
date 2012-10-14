#include "eratos.h"
#include "benchmark.h"

#include <stdio.h>

enum bool {false, true};
typedef enum bool bool;

void test_eratos()
{
	unsigned long count = 0;
	uint64_t *primes = NULL;
	bool passed = true;
	unsigned i;
	


	printf("Primes below 15485863 == 1000000?\n");
	count = eratos(15485863, NULL);
	passed = count == 1000000;
	if (!passed)
		printf("\tFailed. %lu should be 1000000.", count);
	else
		printf("\tPassed.");
	printf("\n");


	printf("Primes below 30 == [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]?\n");
	uint64_t answer [10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	count = eratos(30, &primes);
	passed = count == 10;
	for(i = 0; i < count; i++)
	{
		if(answer[i] != primes[i])
		{
			passed = false;
			break;
		}
	}
	if(!passed)
	{
		printf("\tFailed.\n\tprimes == [");
		for(i = 0; i < count - 1; i++)
		{
			printf("%" PRIu64 ", ", primes[i]);
		}
		printf("%" PRIu64 "]", primes[i]);
	}
	else
	{
		printf("\tPassed.");
	}
	printf("\n");

	//next test
}

void time_eratos(uint64_t n)
{
	double counter;
	size_t prime_count;
	uint64_t *primes;

	startTimer();
	prime_count = eratos(n, &primes);
	counter = getTimer();
	
	if(prime_count != 0 && counter != -1)
	{
		printf("Generating and storing primes below %" PRIu64 " took %0.4f seconds.\n", n, counter);
	}
}

int main()
{
	uint64_t test_nums [] = {30, 1e5, 1e6, 15485863, 1e8};
	unsigned i;

	test_eratos();

	for(i = 0; i < sizeof(test_nums) / sizeof(test_nums[0]); i++)
	{
		time_eratos(test_nums[i]);
	}

	return 0;
}