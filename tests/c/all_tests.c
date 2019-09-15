#include "CuTest.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#include <stdio.h>
// #include <stdlib.h>

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
	for (i = 0; i < ARRAY_SIZE(suites); i += 1) {
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
