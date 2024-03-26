#ifndef GENERATOR_H
#define GENERATOR_H

#include <stddef.h>
#include "buffer.h"

size_t begin_paragraph(struct Buffer *buffer);
size_t end_paragraph(struct Buffer *buffer); 

#endif /* GENERATOR_H */
