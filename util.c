#include "util.h"
#include <x86intrin.h>  // For rdtscp and other intrinsics

// Get the current time stamp counter
CYCLES get_time() {
    unsigned int aux;
    return __rdtscp(&aux);
}

// Measure access time to a single cache line (used for timing cache hits/misses)
int measure_one_block_access_time(void *addr) {
    CYCLES start = get_time();
    asm volatile("mov (%0), %%eax" : : "r" (addr) : "eax");
    CYCLES end = get_time();
    return (int)(end - start);
}
