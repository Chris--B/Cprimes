#pragma once

#include <cprimes_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Check if 2**@p power - 1 is a Mersenne Prime

	Numbers in the form of 2**n - 1 for some integer @a n are called
	Mersenne numbers and are detonated as M(@a n). When these are prime,
	they are called Mersenne primes.
	This function uses the Lucas Lehmer method to check if M(@p power)
	is prime.

	This method is a faster primality test than Miller Rabin, but it
	only works on Mersenne numbers.

	@returns This function returns nonzero when 2**@p power - 1 is prime,
	otherwise 0.

	Example Usage
	@code{.c}
		unsigned powers[] = {3, 5, 7, 11, 13, 17};
		unsigned mersenne;
		int prime;
		size_t i;

		for(i = 0; i < ARRAY_SIZE(powers); ++i) {
			mersenne = (1 << powers[i]) - 1;
			prime = lucas_lehmer(powers[i]);
			printf("p == %u, M(p) == %u, %s\n",
				powers[i], mersenne, prime ? "Prime" : "");
		}
	@endcode
	Prints
	@code{.txt}
		p == 3, M(p) == 7, Prime
		p == 5, M(p) == 31, Prime
		p == 7, M(p) == 127, Prime
		p == 11, M(p) == 2047,
		p == 13, M(p) == 8191, Prime
		p == 17, M(p) == 131071, Prime
	@endcode

	@warning If @p power is not prime, the results are
	meaningless. No check for primeness is performed.

*/
CPRIMES_EXPORT int lucas_lehmer(unsigned power);

#ifdef __cplusplus
}
#endif
