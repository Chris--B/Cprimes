#include "miller_rabin.h"

#include <gmp.h>
#include <string.h>

enum {false, true};

const char* false_positives[] = {
	"2047", "1373653", "25326001", "3215031751", "2152302898747", "3474749660383", "341550071728321", "3825123056546413051",
	NULL
};

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
	
	uint64_t s = 0;
	int maybe_prime;
	int i;
	
	for(i = 0; false_positives[i]; ++i) {
		if(!strcmp(num_str, false_positives[i])) {
			maybe_prime = false;
			goto end;
		}
	}

	mpz_init_set_str(num, num_str, 10);

	mpz_init_set(d, num);
	mpz_sub_ui(d, d, 1);

	mpz_init(a);

	mpz_init(tmp);
	mpz_mod_ui(tmp, num, 2);
	if(!mpz_cmp_ui(tmp, 0) && mpz_cmp_ui(num, 2)) { //num is even and not 2
		maybe_prime = false;
		goto end;
	}

	while(!mpz_cmp_ui(d, 2)) {
		mpz_div_ui(d, d, 2);
		++s;
	}

	for(i = 0; i < 20; ++i) {
		//pick an a
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
	return maybe_prime;
}