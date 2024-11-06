// message.c
#include "message.h"

// volatile char message[MESSAGE_BITS * CACHE_LINE_SIZE];  // Define the shared message array
volatile char message[MESSAGE_BITS * CACHE_LINE_SIZE] = {0};  // Define with zero initialization
