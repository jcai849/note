#include <string.h>

#include "acutest.h"
#include "note.h"
#include "buffer.h"

void test_testing(void) { TEST_CHECK(1); }

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

void test_parse(void) {
	TEST_CHECK(string_parse("", NULL, 0));
}

void test_multiple_parses(void) {
	TEST_CHECK(string_parse("", NULL, 0));
	TEST_CHECK(string_parse("", NULL, 0));
	TEST_CHECK(string_parse("", NULL, 0));
}

void test_parse_text(void) {
	char parser_alloc[30];
	char checker_alloc[30];
	struct Buffer checker_buffer;

	char test_string_1[] = "Lorem Ipsum";
	/*
	char test_string_2[] = "Lorem\nIpsum";
	char test_string_3[] = "\nLorem\nIpsum";
	char test_string_4[] = "\nLorem\nIpsum\n";
	char test_string_5[] = "\n\nLorem\nIpsum\n";

	char test_string_6[] = "\n\nLorem\n\nIpsum\n";
	char test_string_7[] = "\n\nLorem\n\nIpsum\n\n";
	char test_string_8[] = "\n\nLorem\n\nIpsum\n\n";

	char test_string_9[] = "123456789012345678901234567890";
	*/

	init_buffer(&checker_buffer, checker_alloc, LENGTH(checker_alloc));

	string_parse(test_string_1, parser_alloc, LENGTH(parser_alloc));
	begin_paragraph(&checker_buffer);
	write_buffer(&checker_buffer, test_string_1);
	end_paragraph(&checker_buffer);
	TEST_CHECK(strcmp(parser_alloc, checker_alloc) == 0);
	clear_buffer(&checker_buffer);
}

TEST_LIST = {
	{ "the testing framework is working", test_testing },
	{ "write_buffer buffer element is equivalent to string less than buffer size", test_buffer_w_smaller_string },
	{ "write_buffer returns with nonzero if string is equal or greater than buffer size", test_buffer_w_larger_string },
	{ "multiple buffer writes are equivalent to the input strings", test_buffer_w_multiple_strings },
	{ "the string_parse() performs a parse", test_parse },
	{ "multiple parses are allowed for", test_multiple_parses },
	{ "sring_parse of text with no link is equivalent to make_text", test_parse_text },
	{ NULL, NULL }     /* zeroed record marking the end of the list */
};

/* FEATURES
 *
 * html:
 * 
 * sring_parse of text with link only is equivalent to make_link
 * string_parse of text x link is equivalent to make_text x make_link
 *
 * graph:
 * Equivalent to above
 *
 * latex:
 * ditto
 *
 * next:
 * file output
 * transclusion accounted for
 * build system: logging of dependencies, builds of dependencies
 * 
*/
