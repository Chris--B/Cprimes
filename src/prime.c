#include "eratos.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void usage()
{
	printf("Usage: ./primes number\n");
	exit(1);
}

int main(int argc, char** argv)
{
	uint64_t* primes = NULL;
	int num = (argc == 2) ? strtoll(argv[1], NULL, 0) : 15485863;
	size_t len = eratos_sieve(num, &primes);

	printf("%zu\n", len);

	return 0;
}