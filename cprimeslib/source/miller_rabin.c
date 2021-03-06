#include <cprimes.h>

#include "util.h"

#include <gmp.h>

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

static const uint64_t primes_cache [] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257
};

#define PRIMES_CACHE_LEN (sizeof(primes_cache) / sizeof(primes_cache[0]))
#define PRIMES_CACHE_MAX primes_cache[PRIMES_CACHE_LEN - 1]

/*
	Run a single round of the Miller-Rabin primality test.

	Pass in arbitrarily large numbers NUM and D s.t.
		NUM - 1 == D * 2 ^ S, where D, S, and NUM are integers. D and NUM must be odd.
	S isn't a big int because it doesn't need to be: To overflow s, you'd need a number more than 10^18 digits long.
	No checks on D and S are made, so if you choose values which do not satisfy the above equation, good luck.
*/
static int miller_rabin_round(mpz_t* num, mpz_t* a, mpz_t* d, uint64_t s) {
	mpz_t tmp;
	mpz_t num_1;

	unsigned j;
	int maybe_prime = 0;

	mpz_init(tmp);

	mpz_init_set(num_1, *num); /* num_1 == num - 1 */
	mpz_sub_ui(num_1, num_1, 1);

	/*
		num might be prime if:
			a ^ d mod num == 1
	*/
	mpz_powm(tmp, *a, *d, *num);
	if(mpz_cmp_ui(tmp, 1) == 0) {
		maybe_prime = 1;
		goto end;
	}

	/*
		OR
		there exist j in [0, s) s.t.:
			a ^ (d * 2^j) mod num == num - 1
	*/
	for(j = 0; j < s; ++j) {
		mpz_powm(tmp, *a, *d, *num);
		if(mpz_cmp(tmp, num_1) == 0) {
			maybe_prime = 1;
			goto end;
		}
		mpz_mul_ui(*d, *d, 2);
	}

end:
	mpz_clear(tmp);
	mpz_clear(num_1);
	return maybe_prime;
}

/*
	Returns nonzero when the number in num_str is probably prime.
*/
CPRIMES_EXPORT int miller_rabin(const char* num_str) {
	int maybe_prime;
	size_t i;

	uint64_t s;

	mpz_t num;
	mpz_t d;
	mpz_t a;
	mpz_t tmp;

	mpz_init_set_str(num, num_str, 10);

	mpz_init_set(d, num);
	mpz_sub_ui(d, d, 1);

	mpz_init(a);

	mpz_init(tmp);

	/* Doesn't play nice for small numbers.... */
	if(mpz_cmp_ui(num, PRIMES_CACHE_MAX + 1) < 0) {
		for(i = 0; i < PRIMES_CACHE_LEN; ++i) {
			if(!mpz_cmp_ui(num, primes_cache[i])) {
				maybe_prime = 1;
				goto end;
			}
		}
		maybe_prime = 0;
		goto end;
	} else {
		for(i = 0; i < PRIMES_CACHE_LEN; ++i) {
			/* Just your friendly neighborhood trivial division */
			if(mpz_divisible_ui_p(num, primes_cache[i])) {
				maybe_prime = 0;
				goto end;
			}
		}
	}

	if(mpz_even_p(num)) {
		if(!mpz_cmp_ui(num, 2)) {
			maybe_prime = 1; /* 2 is prime */
		} else {
			maybe_prime = 0; /* no other evens are */
		}
		goto end;
	}

	/* get D and S ready for _miller_round */
	for(s = 0; mpz_even_p(d); ++s) {
		mpz_divexact_ui(d, d, 2);
	}

	/* select witnesses from the list of primes */
	for(i = 0; i < PRIMES_CACHE_LEN; ++i) {
		mpz_set_ui(a, primes_cache[i]);
		mpz_set(tmp, d);
		if(!miller_rabin_round(&num, &a, &tmp, s)) {
			maybe_prime = 0;
			goto end;
		}
	}
	maybe_prime = 1;
end:
	mpz_clear(num);
	mpz_clear(d);
	mpz_clear(a);
	mpz_clear(tmp);
	return maybe_prime;
}

/* for benchmarking */
int gmp_miller_rabin(const char* num_str, int rounds) {
	mpz_t num;
	int res;
	mpz_init_set_str(num, num_str, 10);
	res = mpz_probab_prime_p(num, rounds);
	mpz_clear(num);
	return res;
}

#ifdef __cplusplus
}
#endif
