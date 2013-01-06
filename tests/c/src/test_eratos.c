#include "CuTest.h"
#include "eratos.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

void test_below_31_correct(CuTest* tc)
{
	char buff[100];
	uint64_t knowns[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	uint64_t* primes = NULL;
	
	size_t len = 0;
	unsigned i;
	int res;

	res = eratos(31, &primes, &len);

	CuAssert(tc, strerror(res), res == 0);
	CuAssert(tc, "Length was not correct.", len == 10);
	for(i = 0; i < len; ++i) {
		snprintf(buff, 100, "\n\tPrime at index %u was %.0f, but expected %.0f.", i, (double)primes[i], (double)knowns[i]);
		CuAssert(tc, buff, primes[i] == knowns[i]);
	}
}

CuSuite* EratosGetSuite()
{
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, test_below_31_correct);
	return suite;
}