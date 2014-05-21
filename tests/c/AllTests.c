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
    CuSuite* suites[] = {
        EratosGetSuite(),
        EstimateGetSuite(),
        LucasLehmerGetSuite(),
        MillerRabinGetSuite(),
    };

    size_t i;
    for (i = 0; i < sizeof(suites)/sizeof(suites[0]); i += 1) {
        if (suites[i] == NULL) {
            fprintf(stderr, "Suite pointer was null. Skipping.\n");
        }
        CuSuiteRun(suites[i]);

        CuString *output = CuStringNew();

        CuSuiteSummary(suites[i], output);
        CuSuiteDetails(suites[i], output);
        printf("%s\n", output->buffer);

        CuStringDelete(output);
        CuSuiteDelete(suites[i]);
        suites[i] = NULL;
    }
}

int main(void) {
    RunAllTests();
    return 0;
}
