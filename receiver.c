#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "message.h"  // Include the shared message header

#define MESSAGE_BITS 512               // Ensure this matches sender
#define CACHE_LINE_SIZE 64
#define LLC_S_LATENCY 120              // Adjust this based on profiling

void detect_bit(int index, int* result) {
    if (index >= 0 && index < MESSAGE_BITS) {  // Bounds check
        volatile char *addr = &message[index * CACHE_LINE_SIZE];
        CYCLES access_time = measure_one_block_access_time((const void*)addr);

        // Debug output for each bit access
        printf("Detecting bit at index %d: access_time=%u\n", index, access_time);

        result[index] = (access_time > LLC_S_LATENCY) ? 1 : 0;
    } else {
        printf("Index %d is out of bounds\n", index);  // Catch out-of-bounds access
    }
}

void* receiver_func(void* param) {
    int result[MESSAGE_BITS] = {0};  // Allocate exactly MESSAGE_BITS size to prevent overflow
    int index = 0;

    // Start timing
    CYCLES start_time = get_time();

    // Loop to detect each bit in the message, with a safety check
    for (index = 0; index < MESSAGE_BITS; index++) {
        detect_bit(index, &result[index]);
    }

    // End timing
    CYCLES end_time = get_time();
    double total_time_sec = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Calculate and print throughput
    double kb_received = (MESSAGE_BITS / 8.0) / 1024.0;  // Convert bits to KB
    double throughput_kbps = kb_received / total_time_sec;
    printf("Receiver Throughput: %f KB/s\n", throughput_kbps);

    // Print received message safely
    printf("Received message (first 64 bits for verification): ");
    for (int i = 0; i < 64 && i < MESSAGE_BITS; i++) {
        printf("%d", result[i]);
    }
    printf("\n");

    return NULL;
}

int main() {
    printf("Receiver starting...\n");

    // Run receiver function (for simplicity, run directly here without threads)
    receiver_func(NULL);

    printf("Receiver finished.\n");
    return 0;
}
