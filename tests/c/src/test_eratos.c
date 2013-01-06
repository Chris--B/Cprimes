#include "CuTest.h"
#include "eratos.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

void test_0_is_empty(CuTest* tc)
{
	uint64_t* primes = NULL;
	size_t len = 0;
	int res;
	res = eratos(0, &primes, &len);
	CuAssert(tc, strerror(res), res == 0);
	CuAssertf(tc, len == 0, "\n\tLength was %.0f instead of 0.", (double) len);
}

void test_below_31_correct(CuTest* tc)
{
	uint64_t knowns[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	uint64_t* primes = NULL;
	
	size_t len = 0;
	unsigned i;
	int res;
	res = eratos(31, &primes, &len);

	CuAssert(tc, strerror(res), res == 0);
	CuAssertf(tc, len == 10, "Length was %.0f instead of 10.", (double)len);
	for(i = 0; i < len; ++i) {
		CuAssertf(tc, primes[i] == knowns[i], 
			"\n\tPrime at index %u was %.0f, but expected %.0f.", i, (double)primes[i], (double)knowns[i]);
	}
}

void test_15mil_is_1mil_long(CuTest* tc)
{
	uint64_t* primes = NULL;
	size_t len = 0;
	int res;

	res = eratos(15485864, &primes, &len);
	CuAssert(tc, strerror(res), res == 0);
	CuAssertf(tc, len == 1000000, "\n\tLength was %.0f, but expected 1000000.", (double) len);
}

CuSuite* EratosGetSuite()
{
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, test_below_31_correct);
	SUITE_ADD_TEST(suite, test_0_is_empty);
	SUITE_ADD_TEST(suite, test_15mil_is_1mil_long);
	return suite;
}