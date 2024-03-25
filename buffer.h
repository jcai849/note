#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>

#define LENGTH(A) sizeof A / sizeof A[0]

struct Buffer {
        char *buffer;
        int current_position;
        size_t size;
};

void init_buffer(struct Buffer *buffer, char *alloc, int size);
void clear_buffer(struct Buffer *buffer);
size_t write_buffer(struct Buffer *buffer, char *source);

#endif /* BUFFER_H */
