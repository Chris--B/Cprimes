#pragma once

#include "defines.h"

#include <inttypes.h>

START_EXTERN_C

int millerrabin_round(const char* num_str, const char* d_str, uint64_t s, uint64_t witness);

END_EXTERN_C
