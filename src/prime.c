#include <stdio.h>
#include <stdlib.h>

#include "eratos.h"

int main(int argc, char** argv)
{
	prime_t* primes = NULL;
	int num = (argc == 2) ? strtoll(argv[1], NULL, 0) : 15485863;
	size_t len = eratos_sieve(num, &primes);

	printf("%zu\n", len);
	return 0;
}