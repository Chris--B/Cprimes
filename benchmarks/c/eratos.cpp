#include <celero/Celero.h>
#include <eratos.h>

CELERO_MAIN;

BASELINE(Eratos, Below100, 0, 100) {
	uint64_t *primes = nullptr;
	size_t len = 0;
	int err;

	celero::DoNotOptimizeAway((err = eratos(1000, &primes, &len)));
	if (err) {
		// error!
	}
}