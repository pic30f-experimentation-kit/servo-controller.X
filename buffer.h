#ifndef BUFFER_H
#define	BUFFER_H

#define BUFFER_SIZE 32

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

int bufferIsEmpty(Buffer *buffer);

#ifdef TEST
void testBuffer();
#endif

#endif	/* BUFFER_H */

