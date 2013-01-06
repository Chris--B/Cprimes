#include "CuTest.h"
#include "miller_rabin.h"

CuSuite* MillerRabinGetSuite()
{
	CuSuite* suite = CuSuiteNew();

	return suite;
}