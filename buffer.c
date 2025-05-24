#include "buffer.h"
#include "test.h"

void bufferInitialize(Buffer *buffer) {
    buffer->in = buffer->buffer;
    buffer->out = buffer->in;
    buffer->limit = buffer->in + BUFFER_SIZE;
}

void bufferWrite(Buffer *buffer, int data) {
    *(buffer->in) = data;
    buffer->in++; 
}

int bufferRead(Buffer *buffer) {
    int data = *(buffer->out);
    buffer->out++;
    return data;
}

int bufferIsEmpty(Buffer *buffer) {
    return 0;
}

#ifdef TEST
void test_can_write_and_read() {
    Buffer buffer;
    bufferInitialize(&buffer);
    
    bufferWrite(&buffer, 10);
    bufferWrite(&buffer, 20);
    
    assertEquals("BUFF_RE01", 10, bufferRead(&buffer));
    assertEquals("BUFF_RE02", 20, bufferRead(&buffer));
}

void testBuffer() {
    test_can_write_and_read();
}
#endif
