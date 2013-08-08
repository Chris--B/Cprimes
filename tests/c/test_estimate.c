#include "CuTest.h"
#include "eratos.h"
#include "estimate.h"

#include <errno.h>
#include <string.h>

#define define_estimate_test(num) \
	void estimate_##num(CuTest* tc) { \
		uint64_t low_res; \
		uint64_t high_res; \
		uint64_t good_res; \
\
		low_res = low_estimate(num); \
		high_res = high_estimate(num); \
		good_res = good_estimate(num); \
\
		CuAssertf(tc, low_res <= good_res, "good is less than low! (%"PRIu64 " < " "%" PRIu64 ")", good_res, low_res); \
		CuAssertf(tc, low_res <= high_res, "low is greater than high! (%"PRIu64 " > " "%" PRIu64 ")", low_res, high_res); \
		CuAssertf(tc, good_res <= high_res, "good is greater than high! (%"PRIu64 " > " "%" PRIu64 ")", good_res, high_res); \
	}

#define define_eratos_in_estimate_bounds_test(num) \
	void eratos_in_estimate_bounds_##num(CuTest* tc) { \
		uint64_t low_res; \
		uint64_t high_res; \
\
		uint64_t *primes; \
		size_t actual; \
		int err; \
\
		err = eratos(num, &primes, &actual); \
		CuAssertf(tc, err == 0, "eratos(%" PRIu64") failed: %s", (uint64_t)num, strerror(err)); \
\
		low_res = low_estimate(num); \
		high_res = high_estimate(num); \
\
		CuAssertf(tc, low_res <= actual, "low_estimate is too large, or eratos is broken (%"PRIu64" < %"PRIu64")", (uint64_t)actual, low_res ); \
		CuAssertf(tc, actual <= high_res, "high_estimate is too small, or eratos is broken (%"PRIu64" > %"PRIu64")", (uint64_t)actual, high_res ); \
	}

define_estimate_test(598)
define_estimate_test(599)
define_estimate_test(600)
define_estimate_test(601)
define_estimate_test(355990)
define_estimate_test(355991)
define_estimate_test(355992)

define_eratos_in_estimate_bounds_test(598)
define_eratos_in_estimate_bounds_test(599)
define_eratos_in_estimate_bounds_test(600)
define_eratos_in_estimate_bounds_test(601)
define_eratos_in_estimate_bounds_test(355990)
define_eratos_in_estimate_bounds_test(355991)
define_eratos_in_estimate_bounds_test(355992)

CuSuite* EstimateGetSuite() {
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, estimate_598);
	SUITE_ADD_TEST(suite, estimate_599);
	SUITE_ADD_TEST(suite, estimate_600);
	SUITE_ADD_TEST(suite, estimate_601);
	SUITE_ADD_TEST(suite, estimate_355990);
	SUITE_ADD_TEST(suite, estimate_355991);
	SUITE_ADD_TEST(suite, estimate_355992);

	SUITE_ADD_TEST(suite, eratos_in_estimate_bounds_598);
	SUITE_ADD_TEST(suite, eratos_in_estimate_bounds_599);
	SUITE_ADD_TEST(suite, eratos_in_estimate_bounds_600);
	SUITE_ADD_TEST(suite, eratos_in_estimate_bounds_601);
	SUITE_ADD_TEST(suite, eratos_in_estimate_bounds_355990);
	SUITE_ADD_TEST(suite, eratos_in_estimate_bounds_355991);
	SUITE_ADD_TEST(suite, eratos_in_estimate_bounds_355992);

	return suite;
}
