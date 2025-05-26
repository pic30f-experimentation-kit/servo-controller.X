#ifndef BUFFER_H
#define	BUFFER_H
#include <stdbool.h>

#define BUFFER_SIZE 32
#define VALUE_WHEN_EMPTY 0

typedef struct {
    int *in;
    int *out;
    int *limit;
    int buffer[BUFFER_SIZE];
} Buffer;

/**
 * Initializes the buffer.
 * Call this method before using the buffer.
 * @param buffer Pointer to the buffer.
 */
void bufferInitialize(Buffer *buffer);

void bufferWrite(Buffer *buffer, int data);

int bufferRead(Buffer *buffer);

bool bufferIsEmpty(Buffer *buffer);

#ifdef TEST
void testBuffer();
#endif

#endif	/* BUFFER_H */

