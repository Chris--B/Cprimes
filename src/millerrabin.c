#include <gmp.h>

#include "primes.h"

/*
	Run a single round of the Miller-Rabin primality test.

	NUM_STR and D_STR are NULL-terminated strings representing arbitrarily large numbers NUM and D s.t.
		NUM - 1 == D * 2 ^ S, where D, S, and NUM are integers. D and NUM must be odd.
	The caller is responsible for finding D and S to satify the above equation.
*/

enum {false, true};

int millerrabin_round(const char* num_str, const char* d_str, uint64_t s, uint64_t witness)
{
	mpz_t num;
	mpz_t d;
	mpz_t a;
	mpz_t tmp;
	mpz_t num_1;
	unsigned j;
	int maybe_prime = false;

	if(mpz_init_set_str(num, num_str, 10))
	{
		//invalid string in NUM_STR
		return false;
	}
	if(mpz_init_set_str(d, d_str, 10))
	{
		//invalid string in NUM_D
		mpz_clear(num);
		return false;
	}

	mpz_init_set_ui(a, witness);
	mpz_init(tmp);
	
	mpz_init_set(num_1, num); //num_1 == num - 1
	mpz_sub_ui(num_1, num_1, 1);

	/*
	num might be prime if:
		a ^ d mod num == 1
	*/
	mpz_powm(tmp, a, d, num);
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
		mpz_powm(tmp, a, d, num);
		if(mpz_cmp(tmp, num_1) == 0)
		{
			maybe_prime = true;
			goto end;
		}
		mpz_mul_ui(d, d, 2);
	}

end:
	mpz_clear(num);
	mpz_clear(a);
	mpz_clear(d);
	mpz_clear(tmp);
	mpz_clear(num_1);
	return maybe_prime;
}