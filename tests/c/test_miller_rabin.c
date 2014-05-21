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
		snprintf(buff, 20, "%u", i);
		if(miller_rabin(buff)) {
			mr_primes[k] = i;
			++k;
		}
	}

	for(i = 1; i < len; ++i) {
		CuAssertf(tc, known[i] == mr_primes[i],
			"Element %u from miller_rabin array should be %" PRIu64 " but was instead %" PRIu64 ".",
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
		"203956878356401977405765866929034577280193993314348263094772646453283062722701277632936616063144088173312372882677123879538709400158306567338328279154499698366071906766440037074217117805690872792848149112022286332144876183376326512083574821647933992961249917319836219304274280243803104015000563790123",
		"531872289054204184185084734375133399408303613982130856645299464930952178606045848877129147820387996428175564228204785846141207532462936339834139412401975338705794646595487324365194792822189473092273993580587964571659678084484152603881094176995594813302284232006001752128168901293560051833646881436219",
		"319705304701141539155720137200974664666792526059405792539680974929469783512821793995613718943171723765238853752439032835985158829038528214925658918372196742089464683960239919950882355844766055365179937610326127675178857306260955550407044463370239890187189750909036833976197804646589380690779463976173"
	};
	size_t len = sizeof(primes) / sizeof (primes[0]);
	size_t i;
	char buff [20];
	for(i = 0; i < len; ++i) {
		snprintf(buff, 15, "%15s", primes[i]);
		snprintf(buff, 20, "%s... ", buff);
		CuAssertf(tc, miller_rabin(primes[i]), "Miller Rabin returned false for large prime %s.", buff);
	}
}

void miller_rabin_big_nonprimes(CuTest* tc) {
	const char* non_prime =
		"743808006803554439230129854961492699151386107534013432918073439524138264842370630061369715394739134090922937332590384720397133335969549256322620979036686633213903952966175107096769180017646161851573147596390153";

	char buff [20];

	snprintf(buff, 15, "%s", non_prime);
	snprintf(buff, 20, "%s... ", buff);
	CuAssertf(tc, !miller_rabin(non_prime), "Miller Rabin returned true for large composite %s.", buff);
}

CuSuite* MillerRabinGetSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, miller_rabin_small_nums);
	SUITE_ADD_TEST(suite, miller_rabin_big_primes);
	SUITE_ADD_TEST(suite, miller_rabin_big_nonprimes);
	return suite;
}
