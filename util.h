#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#define CACHE_LINE_SIZE 64
#define LLC_THRESHOLD 120  // Adjust to the measured LLC latency threshold on local system

typedef uint64_t CYCLES;

CYCLES get_time();
int measure_one_block_access_time(void *addr);

#endif // UTIL_H
