#include "lucas_lehmer.h"

#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>


/*
	Determines if 2^power - 1 is prime
*/
int lucas_lehmer(unsigned power) {
	mpz_t s_seq;
	mpz_t tmp;
	mpz_t M;

	size_t i;
	int res;

	/* The test doesn't handle 2. */
	if(power == 2) {
		return 1;
	}

	mpz_init_set_ui(s_seq, 4);
	mpz_init_set_ui(tmp, 2);
	mpz_init(M);

	/* error checking please... */

	mpz_pow_ui(M, tmp, power);
	mpz_sub_ui(M, M, 1);

	for(i = 0; i < power - 2; ++i) {
		mpz_powm_ui(tmp, s_seq, 2, M);
		mpz_sub_ui(tmp, tmp, 2);

		mpz_mod(s_seq, tmp, M);
	}
	res =  mpz_cmp_ui(s_seq, 0) == 0;

	mpz_clear(s_seq);
	mpz_clear(tmp);
	mpz_clear(M);

	return res;
}
