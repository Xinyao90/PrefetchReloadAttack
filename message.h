// message.h
#ifndef MESSAGE_H
#define MESSAGE_H

#include "util.h"

#define MESSAGE_BITS 512
#define CACHE_LINE_SIZE 64

// Declare the message array as extern so both files can access it
extern volatile char message[MESSAGE_BITS * CACHE_LINE_SIZE];

#endif // MESSAGE_H
