/* This is auto-generated code. Edit at your own peril. */
#include <stdio.h>
#include <stdlib.h>

#include "CuTest.h"

/* Oneline headers are a waste of time */
CuSuite* EratosGetSuite();
CuSuite* MillerRabinGetSuite();
CuSuite* EstimateGetSuite();

void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuiteAddSuite(suite, EratosGetSuite());
    CuSuiteAddSuite(suite, MillerRabinGetSuite());
    CuSuiteAddSuite(suite, EstimateGetSuite());

   	CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    CuStringDelete(output);
    CuSuiteDelete(suite);
}

int main(void) {
    RunAllTests();
    return 0;
}
