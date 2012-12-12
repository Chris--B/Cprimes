#pragma once

#include "defines.h"

START_EXTERN_C

extern uint64_t cache [];
//431 primes, 2 <= p <= 3001
#define CACHE_MAX 3001
#define CACHE_SIZE (sizeof cache / sizeof cache[0])


END_EXTERN_C
