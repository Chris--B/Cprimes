#include "eratos.h"

#include <errno.h>
#include <inttypes.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NO_MODE    0
#define MODE_SIEVE 1
#define MODE_RANGE 2
#define MODE_CHECK 3

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

void usage(int exit_code)
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
	int no_print_flag = 0;

	int sieve_max = 0;         //Used with MODE_RANGE and MODE_SIEVE
	int sieve_min = 0;         //Used with MODE_RANGE
	uint64_t num_to_check = 0; //Used with MODE_CHECK
	
	FILE* outfile = stdout;

	int mode = NO_MODE;

	uint64_t* primes = NULL;
	size_t primes_len = 0;

	if(argc == 1) usage(1);

	while((c = getopt_long(argc, argv, "c:s:r:o:nh", long_options, (int*)0 )) != -1)
	{
		switch (c)
		{
			//check if prime
			case 'c':
				check_mode(mode);
				mode = MODE_CHECK;
				sscanf(optarg, "%" SCNu64, &num_to_check);
				break;

			case 'r':
				check_mode(mode);
				mode = MODE_RANGE;
				fprintf(stderr, "Not implemented.\n");
				break;

			//or setup a sieve
			case 's':
				check_mode(mode);
				sieve_max= atoi(optarg);
				mode = MODE_SIEVE;
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

			case 'n':
				no_print_flag = 1;
				break;

			case 'h': case '?':
				usage(2);
				break;
		}
	}

	//while(opti)

	switch(mode)
	{
		case MODE_SIEVE:
			if(no_print_flag)
			{
				fprintf(outfile, "Total: %zu\n", eratos_sieve(sieve_max, NULL));	
			}
			else
			{
				fprintf(outfile, "Total: %zu\n", (primes_len = eratos_sieve(sieve_max, &primes)));	
				for(size_t i = 0; i < primes_len; i++)
				{
					fprintf(outfile, "%" PRIu64 " ", primes[i]);
				}
				printf("\n");
				free(primes);
			}
			break;

		case MODE_RANGE:
			fprintf(stderr, "--range not yet implemented.\n");
			break;
		case MODE_CHECK:
			fprintf(stderr, "--check not yet implemented.\n");
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