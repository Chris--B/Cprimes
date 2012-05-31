#include "eratos.h"

#include <errno.h>
#include <inttypes.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NO_MODE    0
#define MODE_BELOW 1
#define MODE_RANGE 2
#define MODE_COUNT 3

static const struct option long_options[] =
{
	{"count",    required_argument, NULL, 'c'},
	{"in-range", required_argument, NULL, 'r'},
	{"below",    required_argument, NULL, 'b'},
	{"out",      required_argument, NULL, 'o'},
	{"help",     no_argument,       NULL, 'h'},
	{NULL,       no_argument,       NULL, 0}
};

void usage(int exit_code)
{
	printf("Find prime numbers.\n");
	printf(
"Options:\n\
   [-c | --count X]        Counts primes less than or equal to X.\n\
   [-r | --in-range Y X]   Sieves from Y to X and prints all primes in range.\n\
   [-b | --below X]        Sieves from 0 to X and prints all primes in range.\n\
                             Same as -r 0 X\n\
   [-o | --out FILE]       Change output from stdout to FILE\n\
   [-h | --help]           Displays this information.\n");
	exit(exit_code);
}

void check_mode(int mode)
{
	if(mode)
	{
		fprintf(stderr, "You can only use one -c, -r, or -s.\n");
		exit(1);
	}
}

int main(int argc, char** argv)
{
	int c;

	int sieve_max = 0;         //Used with MODE_RANGE and MODE_BELOW
	int sieve_min = 0;         //Used with MODE_RANGE
	
	FILE* outfile = stdout;

	int mode = NO_MODE;

	uint64_t* primes = NULL;
	size_t primes_count = 0;

	if(argc == 1) usage(1);

	while((c = getopt_long(argc, argv, "c:r:b:o:h", long_options, (int*)0 )) != -1)
	{
		switch (c)
		{
			//check if prime
			case 'c':
				check_mode(mode);
				mode = MODE_COUNT;
				sscanf(optarg, "%" SCNu64, &sieve_max);
				break;

			case 'r':
				check_mode(mode);
				mode = MODE_RANGE;
				fprintf(stderr, "Not implemented.\n");
				break;

			//or setup a sieve
			case 'b':
				check_mode(mode);
				sieve_max= atoi(optarg);
				mode = MODE_BELOW;
				break;

			//change output
			case 'o':
				errno = 0;
				if(outfile != stdout)
				{
					fprintf(stderr, "Redefining --out. Stop that.\n");
					exit(5);	
				}
				outfile = fopen(optarg, "w");
				if(!outfile)
				{
					fprintf(stderr, "Error opening %s: %s\n", optarg, strerror(errno));
					exit(1);
				}
				break;

			case 'h':
				usage(2);
				break;
			case '?':
				break;
		}
	}

	switch(mode)
	{
		case MODE_BELOW:
			primes_count = eratos_sieve(sieve_max, &primes);
			for(size_t i = 0; i < primes_count; i++)
			{
				fprintf(outfile, "%" PRIu64 " ", primes[i]);
			}
			printf("\n");
			free(primes);
			break;

		case MODE_RANGE:
			fprintf(stderr, "--range not yet implemented.\n");
			break;
		case MODE_COUNT:
			fprintf(outfile, "%zu\n", eratos_sieve(sieve_max, NULL));	
			break;
		case NO_MODE:
			fprintf(stderr, "No mode selected.\n");
			usage(1);
			break;
		default:
			fprintf(stderr, "Unknown mode.\n");
			break;
	}

	fclose(outfile);
	return 0;
}