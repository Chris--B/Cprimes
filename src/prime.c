#include "eratos.h"

#include <errno.h>
#include <inttypes.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static const struct option long_options[] =
{
	{"check",    required_argument, NULL, 'c'},
	{"sieve",    required_argument, NULL, 's'},
	{"range",    required_argument, NULL, 'r'},
	{"out",      required_argument, NULL, 'o'},
	{"no-print", no_argument,       NULL, 'n'},
	{"help",     no_argument,       NULL, 'h'},
	{NULL,       no_argument,       NULL, 0}
};

void usage()
{
	printf("Find prime numbers.\n");
	printf(
"Options:\n\
   [-c | --check X]        Checks whether or not X is prime.\n\
   [-r | --range Y X]      Sieves from Y to X and prints all primes in range.\n\
   [-s | --sieve X]        Sieves from 0 to X and prints all primes in range.\n\
                             Same as -r 0 X\n\
   [-o | --out FILE]       Change output from stdout to FILE\n\
   [-n | --no-print]       No primes will be printed. Only counted.\n\
                              Use with -s.\n\
   [-h | --help]           Displays this information.\n");
	exit(1);
}

int main(int argc, char** argv)
{
	int c;
	int no_print_flag = 0;
	int sieve_max = 0;
	uint64_t num_to_check = 0;
	FILE* outfile = stdout;

	uint64_t* primes = NULL;
	size_t len = 0;

	if(argc == 1) usage();

	while((c = getopt_long(argc, argv, "c:s:r:o:nh", long_options, (int*)0 )) != -1)
	{
		switch (c)
		{
			//check if prime
			case 'c':
				sscanf(optarg, "%" SCNu64, &num_to_check);
				//Now do something with num_to_check....
			case 'r':
				fprintf(stderr, "Not implemented.\n");
				exit(3);
				break;
			//or setup a sieve
			case 's':
				sieve_max= atoi(optarg);
				break;
			//change output
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
				no_print_flag = 1;
				break;
			case 'h': case '?':
				usage();
				break;
		}
	}

	if(no_print_flag)
	{
		len = eratos_sieve(sieve_max, NULL);	
	}
	else
	{
		len = eratos_sieve(sieve_max, &primes);
	}

	fprintf(outfile, "Total: %zu\n", len);
	
	for(size_t i = 0; i < len; i++)
	{
		fprintf(outfile, "%" PRIu64 "\n", primes[i]);
	}

	fclose(outfile);
	return 0;
}