#pragma once

#include <cprimes_platform.h>

#include <inttypes.h>


#ifdef __cplusplus
extern "C" {
#endif

CPRIMES_EXPORT int miller_rabin(const char* num_str);

#ifdef __cplusplus
}
#endif
