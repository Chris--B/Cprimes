#include <celero/Celero.h>
#include <eratos.h>

CELERO_MAIN;

static void run_eratos(size_t num) {
	uint64_t *primes = nullptr;
	size_t len = 0;
	int err;

	celero::DoNotOptimizeAway((err = eratos(num, &primes, &len)));
	if (err) {
		exit(0);
	}
}

BASELINE(Eratos, Below100, 0, 10000) {
	run_eratos(100);
}

BENCHMARK(Eratos, Below1000, 0, 10000) {
	run_eratos(1000);
}