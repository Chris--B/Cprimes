#include "defines.h"
#include "CuTest.h"
#include "eratos.h"
#include "miller_rabin.h"

#include <stdio.h>
#include <string.h>

void miller_rabin_small_nums(CuTest* tc) {
	#define limit 10000

	char buff[20]; /* 64-bit ints won't get larger than 18 digits */

	uint64_t *known = NULL;
	uint64_t *mr_primes = NULL;

	size_t len;
	size_t i, k;

	int res;

	res = eratos(limit, &known, &len);
	CuAssert(tc, strerror(res), res == 0);

	mr_primes = malloc(len * sizeof(uint64_t));

	k = 0;
	for(i = 1; i < limit; i += 1) {
		snprintf(buff, 20, "%u", (unsigned int)i);
		if(miller_rabin(buff)) {
			mr_primes[k] = i;
			++k;
		}
	}

	for(i = 1; i < len; ++i) {
		CuAssertf(tc, known[i] == mr_primes[i],
			"Element %u from miller_rabin array should be %" PRIu64
			" but was instead %" PRIu64 ".",
			i, known[i], mr_primes[i]);
	}
	#undef limit
	free(known);
	free(mr_primes);
}

void miller_rabin_big_primes(CuTest* tc) {
	/* #http://primes.utm.edu/lists/small/ */
	/* 300-digit primes */
	const char* primes []= {
		"2039568783564019774057658669290345772801939933143482630947726464532830"
		"6272270127763293661606314408817331237288267712387953870940015830656733"
		"8328279154499698366071906766440037074217117805690872792848149112022286"
		"3321448761833763265120835748216479339929612499173198362193042742802438"
		"03104015000563790123",

		"5318722890542041841850847343751333994083036139821308566452994649309521"
		"7860604584887712914782038799642817556422820478584614120753246293633983"
		"4139412401975338705794646595487324365194792822189473092273993580587964"
		"5716596780844841526038810941769955948133022842320060017521281689012935"
		"60051833646881436219",

		"3197053047011415391557201372009746646667925260594057925396809749294697"
		"8351282179399561371894317172376523885375243903283598515882903852821492"
		"5658918372196742089464683960239919950882355844766055365179937610326127"
		"6751788573062609555504070444633702398901871897509090368339761978046465"
		"89380690779463976173"
	};
	size_t len = ARRAY_SIZE(primes);
	size_t i;
	char buff [20];
	char buff2 [20];
	for(i = 0; i < len; ++i) {
		/* Limit it to the first 15 digits. */
		snprintf(buff2, 15, "%s...", primes[i]);
		snprintf(buff, 20, "'%s...' ", buff2);
		CuAssertf(tc, miller_rabin(primes[i]), "Miller Rabin returned false for large prime %s.", buff);
	}
}

void miller_rabin_big_nonprimes(CuTest* tc) {
	const char* non_prime =
		"7438080068035544392301298549614926991513861075340134329180734395241382"
		"6484237063006136971539473913409092293733259038472039713333596954925632"
		"2620979036686633213903952966175107096769180017646161851573147596390153"
		;

	char buff [20];
	char buff2 [20];

	snprintf(buff2, 15, "%s", non_prime);
	snprintf(buff, 20, "%s... ", buff2);
	CuAssertf(tc, !miller_rabin(non_prime),
		"Miller Rabin returned true for a large composite %s.", buff);
}

CuSuite* MillerRabinGetSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, miller_rabin_small_nums);
	SUITE_ADD_TEST(suite, miller_rabin_big_primes);
	SUITE_ADD_TEST(suite, miller_rabin_big_nonprimes);
	return suite;
}
