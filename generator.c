#include "buffer.h"

size_t begin_paragraph(struct Buffer *buffer) {
	return write_buffer(buffer, "<p>");
}

size_t end_paragraph(struct Buffer *buffer) {
	return write_buffer(buffer, "<\\p>\n");
}

size_t begin_link(struct Buffer *buffer) {
	return write_buffer(buffer, "<a href=\"");
} 

size_t end_link(struct Buffer *buffer) {
	return write_buffer(buffer, ">link</a>");
} 
