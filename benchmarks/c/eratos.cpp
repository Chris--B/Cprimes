#include <celero/Celero.h>
#include <eratos.h>

#include <cerrno>
#include <cstring>

#include <iostream>

CELERO_MAIN;

static void run_eratos(size_t num) {
	uint64_t *primes = nullptr;
	size_t len = 0;
	int err;

	celero::DoNotOptimizeAway((err = eratos(num, &primes, &len)));
	if (err) {
		std::cerr << "[Error]" << "eratos(" << num << ") " << strerror(err) << "\n";
	}
	free(primes);
}

BASELINE(Eratos, Below1000, 0, 100) {
	run_eratos(1000);
}

BASELINE(Eratos, Below10000, 0, 100) {
	run_eratos(10000);
}

BASELINE(Eratos, Below1_Million, 0, 100) {
	run_eratos(1000000);
}

BASELINE(Eratos, Below10_Million, 0, 5) {
	run_eratos(10000000);
}

BASELINE(Eratos, Below100_Million, 0, 5) {
	run_eratos(100000000);
}
// This kills the computer
BASELINE(Eratos, Below1_Billion, 2, 1) {
	run_eratos(1000000000);
}