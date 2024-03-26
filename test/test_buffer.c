#include "test.h"
#include "buffer.h"

void test_buffer_w_smaller_string(void) {
	char alloc[10];
	struct Buffer buffer;
	char *test_string =  "123456789";

	init_buffer(&buffer, alloc, LENGTH(alloc));
	TEST_CHECK(write_buffer(&buffer, test_string));
	TEST_CHECK(strcmp(alloc, test_string) == 0);
}

void test_buffer_w_larger_string(void) {
	char alloc[10];
	struct Buffer buffer;
	char *test_string_1 =  "123456789X";
	char *test_string_2 =  "123456789XX";

	init_buffer(&buffer, alloc, LENGTH(alloc));
	TEST_CHECK(!write_buffer(&buffer, test_string_1));
	TEST_CHECK(!write_buffer(&buffer, test_string_2));
}

void test_buffer_w_multiple_strings(void) {
	char alloc[10];
	struct Buffer buffer;
	char *test_string   =  "123456789";
	char *test_string_1 =  "123";
	char *test_string_2 =  "456";
	char *test_string_3 =  "789";
	char *test_string_4 =  "X";
	char *test_string_5 =  "XXX";

	init_buffer(&buffer, alloc, LENGTH(alloc));
	TEST_CHECK(write_buffer(&buffer, test_string_1));
	TEST_CHECK(write_buffer(&buffer, test_string_2));
	TEST_CHECK(write_buffer(&buffer, test_string_3));
	TEST_CHECK(strcmp(alloc, test_string) == 0);
	TEST_CHECK(!write_buffer(&buffer, test_string_4));
	TEST_CHECK(strcmp(alloc, test_string) == 0);
	TEST_CHECK(!write_buffer(&buffer, test_string_5));
	TEST_CHECK(strcmp(alloc, test_string) == 0);
}

void test_clear_buffer(void) {
	char alloc[10];
	struct Buffer buffer;
	char *test_string =  "123456789";

	init_buffer(&buffer, alloc, LENGTH(alloc));
	write_buffer(&buffer, test_string);
	clear_buffer(&buffer);
	TEST_CHECK(strcmp(alloc, "") == 0);
	write_buffer(&buffer, test_string);
	TEST_CHECK(strcmp(alloc, test_string) == 0);
}
