#include "eratos.h"

#include <errno.h>
#include <inttypes.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void usage()
{
	printf("Usage: ./primes number\n");
	exit(1);
}

int main(int argc, char** argv)
{
	int c;
	int n_flag = 0;
	int num = 0;
	uint64_t num_to_check = 0;
	FILE* outfile = stdout;

	uint64_t* primes = NULL;
	size_t len = 0;


	while((c = getopt(argc, argv, "c:s:o:nh")) != -1)
	{
		switch (c)
		{
			//check if prime
			case 'c':
				sscanf(optarg, "%" SCNu64, &num_to_check);
				//Now do something with x....
				fprintf(stderr, "Not implemented.\n");
				exit(3);
				break;
			case 's':
				num = atoi(optarg);
				break;
			case 'o':
				errno = 0;
				outfile = fopen(optarg, "w");
				if(!outfile)
				{
					fprintf(stderr, "Error opening %s: %s\n", optarg, strerror(errno));
					exit(1);
				}
				break;
			case 'n':
				n_flag = 1;
				break;
			case 'h':
				usage();
				break;
			case '?':
				exit(2);
				break;
		}
	}
	
	if(n_flag)
	{
		len = eratos_sieve(num, NULL);	
	}
	else
	{
		len = eratos_sieve(num, &primes);
	}

	printf("Total: %zu\n", len);
	
	for(size_t i = 0; i < len; i++)
	{
		fprintf(outfile, "%" PRIu64 "\n", primes[i]);
	}

	fclose(outfile);
	return 0;
}