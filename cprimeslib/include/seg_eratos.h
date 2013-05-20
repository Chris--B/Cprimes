#pragma once

#include "defines.h"

#include <stddef.h>


START_EXTERN_C

int seg_eratos(uint64_t min, uint64_t max, size_t block, uint64_t **primes, size_t *count);

END_EXTERN_C
