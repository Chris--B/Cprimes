#include <cprimes.h>

#include "CuTest.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int is_prime[] = {0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1};

void lucas_lehmer_power_of_n(CuTest* tc, unsigned power) {
	CuAssertf(tc, power/2 < ARRAY_SIZE(is_prime),
		"%u is out of range of lookup table (%f)",
		power,
		(double)ARRAY_SIZE(is_prime));

	if (is_prime[power / 2]) {
		CuAssertf(tc, lucas_lehmer(power),
			"2 ** %u - 1 is prime, but lucas_lehmer() returned false.",
			power);
	} else {
		CuAssertf(tc, !lucas_lehmer(power),
			"2 ** %u - 1 is composite, but lucas_lehmer() returned true.",
			power);
	}
}

#define make_small_test(num)                                              \
	void lucas_lehmer_power_of_##num(CuTest* cu) {                        \
		lucas_lehmer_power_of_n(cu, num);                                 \
	}

make_small_test(2)
make_small_test(3)
make_small_test(5)
make_small_test(7)
make_small_test(9)
make_small_test(11)
make_small_test(13)
make_small_test(15)
make_small_test(17)
make_small_test(19)
make_small_test(21)
make_small_test(23)
make_small_test(25)
make_small_test(27)
make_small_test(29)
make_small_test(31)


CuSuite* LucasLehmerGetSuite() {
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_2);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_3);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_5);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_7);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_9);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_11);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_13);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_15);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_17);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_19);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_21);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_23);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_25);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_27);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_29);
	SUITE_ADD_TEST(suite, lucas_lehmer_power_of_31);

	return suite;
}
