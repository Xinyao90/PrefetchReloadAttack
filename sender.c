#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "message.h"  // Include the shared header file

#define MESSAGE_BITS 512              // Number of bits to send (can also use 256)
#define CACHE_LINE_SIZE 64            // Cache line size in bytes

void encode_bit(int bit, int index) {
    volatile char *addr = &message[index * CACHE_LINE_SIZE];
    if (bit == 1) {
        // Prefetch to encode '1' bit
        __builtin_prefetch((const void*)addr, 1, 3);
    }
    // No prefetch for '0' bit
}

void* sender_func(void* param) {
    // Example message bits array (1 for '1' bit and 0 for '0' bit)
    int message_bits[MESSAGE_BITS] = { /* Define the bit sequence here */ };

    int index = 0;

    // Start timing
    CYCLES start_time = get_time();

    // Loop to encode each bit in the message_bits array
    while (index < MESSAGE_BITS) {
        encode_bit(message_bits[index], index);
        index++;
    }

    // End timing
    CYCLES end_time = get_time();
    double total_time_sec = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Calculate and print throughput
    double kb_sent = (MESSAGE_BITS / 8.0) / 1024.0;  // Convert bits to KB
    double throughput_kbps = kb_sent / total_time_sec;
    printf("Sender Throughput: %f KB/s\n", throughput_kbps);

    return NULL;
}

int main() {
    printf("Sender starting...\n");

    // Run sender function (for simplicity, run directly here without threads)
    sender_func(NULL);

    printf("Sender finished.\n");
    return 0;
}

