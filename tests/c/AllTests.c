/* This is auto-generated code. Edit at your own peril. */
#include <stdio.h>
#include <stdlib.h>

#include "CuTest.h"

/* Oneline headers are a waste of time */
CuSuite* EratosGetSuite();
CuSuite* EstimateGetSuite();
CuSuite* LucasLehmerGetSuite();
CuSuite* MillerRabinGetSuite();


void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuite* eratosSuite = EratosGetSuite();
    CuSuite* estimateSuite = EstimateGetSuite();
    CuSuite* lucasLehmerSuite = LucasLehmerGetSuite();
    CuSuite* millerRabinSuite = MillerRabinGetSuite();

    CuSuiteAddSuite(suite, eratosSuite);
    CuSuiteAddSuite(suite, estimateSuite);
    CuSuiteAddSuite(suite, lucasLehmerSuite);
    CuSuiteAddSuite(suite, millerRabinSuite);

    CuSuiteDelete(eratosSuite);
    CuSuiteDelete(estimateSuite);
    CuSuiteDelete(lucasLehmerSuite);
    CuSuiteDelete(millerRabinSuite);

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
