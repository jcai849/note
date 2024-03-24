#include <string.h>
#include "buffer.h"

void init_buffer(struct Buffer *buffer, char *alloc, int size) {
        buffer->buffer = alloc;
        buffer->current_position = 0;
        buffer->size = size;
}

int write_buffer(struct Buffer *buffer, char *source) {
	size_t source_length = strlen(source);

        if (source_length >= buffer->size - buffer->current_position) return 1;
        else strcpy(buffer->buffer + buffer->current_position, source);
	buffer->current_position += source_length;
        return 0;
}
