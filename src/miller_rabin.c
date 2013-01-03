#include "miller_rabin.h"
#include "eratos.h"

#include <gmp.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

enum {false, true};

//TODO
const char* false_positives[] = {
	NULL
};

//sufficient for num <= 341,550,071,728,321
const uint64_t primes [] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251
};
#define PRIMES_LEN (sizeof(primes) / sizeof(primes[0]))
#define PRIMES_MAX primes[PRIMES_LEN - 1]

/*
	Run a single round of the Miller-Rabin primality test.

	Pass in arbitrarily large numbers NUM and D s.t.
		NUM - 1 == D * 2 ^ S, where D, S, and NUM are integers. D and NUM must be odd.
	S isn't a big int because it doesn't need to be: To overflow s, you'd need a number more than 10^18 digits long.
	No checks on D and S are made, so if you choose values which do not satisfy the above equation, good luck.
*/
int _miller_rabin_round(const mpz_t* num, const mpz_t* d, const mpz_t* a, uint64_t s)
{
	mpz_t tmp;
	mpz_t tmp_d;
	mpz_t num_1;

	unsigned j;
	int maybe_prime = false;

	mpz_init(tmp);
	
	mpz_init_set(tmp_d, *d);

	mpz_init_set(num_1, *num); //num_1 == num - 1
	mpz_sub_ui(num_1, num_1, 1);

	/*
		num might be prime if:
			a ^ d mod num == 1
	*/
	mpz_powm(tmp, *a, tmp_d, *num);
	if(mpz_cmp_ui(tmp, 1) == 0)
	{
		maybe_prime = true;
		goto end;
	}

	/*
		OR
		there exist j in [0, s) s.t.:
			a ^ (d * 2^j) mod num == num - 1
	*/
	for(j = 0; j < s; ++j)
	{
		mpz_powm(tmp, *a, tmp_d, *num);
		if(mpz_cmp(tmp, num_1) == 0)
		{
			maybe_prime = true;
			goto end;
		}
		mpz_mul_ui(tmp_d, tmp_d, 2);
	}

end:
	mpz_clear(tmp);
	mpz_clear(num_1);
	return maybe_prime;
}

/*
	Returns nonzero when the number in num_str is probably prime.
*/
int miller_rabin(const char* num_str)
{
	mpz_t num;
	mpz_t d;
	mpz_t a;
	mpz_t tmp;

	gmp_randstate_t state;

	uint64_t s;
	int maybe_prime;
	size_t i;

	srand(time(NULL));
	
	for(i = 0; false_positives[i]; ++i) {
		if(!strcmp(num_str, false_positives[i])) {
			return false;
		}
	}

	mpz_init_set_str(num, num_str, 10);

	mpz_init_set(d, num);
	mpz_sub_ui(d, d, 1);

	mpz_init(a);

	mpz_init(tmp);

	gmp_randinit_default(state);

	//Doesn't play nice for small numbers....
	if(mpz_cmp_ui(num, PRIMES_MAX + 1) < 0) {
		for(i = 0; i < PRIMES_LEN; ++i) {
			if(!mpz_cmp_ui(num, primes[i])) {
				maybe_prime = true;
				goto end;
			}
		}
		maybe_prime = false;
		goto end;
	}

	if(mpz_even_p(num)) { //even?
		if(!mpz_cmp_ui(num, 2)) {
			maybe_prime = true; //2 is prime
		} else {
			maybe_prime = false; //no other evens are
		}
		goto end;
	}

	//get D and S ready for _miller_round
	for(s = 0; !mpz_cmp_ui(d, 2); ++s) {
		mpz_div_ui(d, d, 2);
	}

	//select witnesses from the list of primes
	for(i = 0; i < PRIMES_LEN && primes[i] < 73; ++i) {
		mpz_set_ui(a, primes[i]);
		if(!_miller_rabin_round(&num, &d, &a, s)) {
			maybe_prime = false;
			goto end;
		}
	}
	maybe_prime = true;
end:
	mpz_clear(num);
	mpz_clear(d);
	mpz_clear(a);
	mpz_clear(tmp);
	gmp_randclear(state);
	return maybe_prime;
}