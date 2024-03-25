#define LENGTH(A) sizeof A / sizeof A[0]
struct Buffer {
        char *buffer;
        int current_position;
        size_t size;
};

void init_buffer(struct Buffer *buffer, char *alloc, int size);
int write_buffer(struct Buffer *buffer, char *source);
void clear_buffer(struct Buffer *buffer);
