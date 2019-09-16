#include <cprimes.h>

#include "util.h"

#include <gmp.h>

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
	Determine if M = 2 ** power - 1 is prime, assuming power is prime.
*/
CPRIMES_EXPORT int lucas_lehmer(unsigned power) {
	mpz_t s_seq;
	mpz_t tmp;
	mpz_t M;

	size_t i;
	int res;

	/* The test doesn't work for power == 2. 2, the only even prime, is always messing stuff up. */
	if (power == 2) {
		return 1;
	}

	mpz_init_set_ui(s_seq, 4);
	mpz_init_set_ui(tmp, 2);
	mpz_init(M);

	/* error checking please... */

	/* M = 2 ** power - 1 */
	mpz_pow_ui(M, tmp, power);
	mpz_sub_ui(M, M, 1);

	for(i = 0; i < power - 2; ++i) {
		/* s_i = s_i-1 ** 2 - 2 */
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

#ifdef __cplusplus
}
#endif
