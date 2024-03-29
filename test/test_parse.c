#include "test.h"
#include "generator.h"
#include "note.h"

void test_parse(void) {
	TEST_CHECK(string_parse("", NULL, 0));
}

void test_multiple_parses(void) {
	TEST_CHECK(string_parse("", NULL, 0));
	TEST_CHECK(string_parse("", NULL, 0));
	TEST_CHECK(string_parse("", NULL, 0));
}

void test_parse_too_big(void) {
	char alloc[10];
	char *test_string =  "123456789X";
	TEST_CHECK(!string_parse(test_string, alloc, LENGTH(alloc)));
}

void test_parse_single_paragraph(void) {
	char parser_alloc[30];
	char checker_alloc[30];
	struct Buffer checker_buffer;
	char *single_p[] = { "Lorem\nIpsum",
                             "\nLorem\nIpsum",
	                     "\n\nLorem\nIpsum\n\n",
	                     "\n\nLorem\nIpsum\n\n\n" };
	char *single_p_trailing_n = "Lorem\nIpsum\n";
	long unsigned int i = 0;

	init_buffer(&checker_buffer, checker_alloc, LENGTH(checker_alloc));

	TEST_CASE("single paragraph");
	for (i = 0; i < LENGTH(single_p); i++) {
		TEST_ASSERT(string_parse(single_p[i], parser_alloc, LENGTH(parser_alloc)));
		TEST_ASSERT(begin_paragraph(&checker_buffer));
		TEST_ASSERT(write_buffer(&checker_buffer, single_p[0]));
		TEST_ASSERT(end_paragraph(&checker_buffer));
		TEST_CHECK(strcmp(parser_alloc, checker_alloc) == 0);
		clear_buffer(&checker_buffer);
	}

	TEST_CASE("single paragraph trailing newline");
	TEST_ASSERT(string_parse(single_p_trailing_n, parser_alloc, LENGTH(parser_alloc)));
	TEST_ASSERT(begin_paragraph(&checker_buffer));
	TEST_ASSERT(write_buffer(&checker_buffer, single_p_trailing_n));
	TEST_ASSERT(end_paragraph(&checker_buffer));
	TEST_CHECK(strcmp(parser_alloc, checker_alloc) == 0);
	clear_buffer(&checker_buffer);
}

void test_parse_multi_paragraph(void) {
	char parser_alloc[30];
	char checker_alloc[30];
	struct Buffer checker_buffer;
	long unsigned int i = 0;
	char *multi_p[]  = { "\n\nLorem\n\t\nIpsum",
                             "\n\nLorem\n\nIpsum",
                             "\nLorem\n\nIpsum\n\n",
                             "\n\nLorem\n\nIpsum\n\n",
                             "\n\nLorem\n\nIpsum\n\n\n",
                             "\n\nLorem\n\n\nIpsum\n\n" };

	init_buffer(&checker_buffer, checker_alloc, LENGTH(checker_alloc));
	
	TEST_CASE("multi paragraph");
	for (i = 0; i < LENGTH(multi_p); i++) {
		TEST_ASSERT(string_parse(multi_p[i], parser_alloc, LENGTH(parser_alloc)));
		TEST_ASSERT(begin_paragraph(&checker_buffer));
		TEST_ASSERT(write_buffer(&checker_buffer, "Lorem"));
		TEST_ASSERT(end_paragraph(&checker_buffer));
		TEST_ASSERT(begin_paragraph(&checker_buffer));
		TEST_ASSERT(write_buffer(&checker_buffer, "Ipsum"));
		TEST_ASSERT(end_paragraph(&checker_buffer));
		TEST_CHECK(strcmp(parser_alloc, checker_alloc) == 0);
		clear_buffer(&checker_buffer);
	}
}

void test_parse_solo_link(void) {
	char parser_alloc[60];
	char checker_alloc[60];
	struct Buffer checker_buffer;
	long unsigned int i = 0;
	char *links[]  = { ">example.com",
	                   "\n>example.com",
	                   ">example.com\n\n" };
	init_buffer(&checker_buffer, checker_alloc, LENGTH(checker_alloc));

	TEST_CASE("solo link");
	for (i = 0; i < LENGTH(links); i++) {
		TEST_ASSERT(string_parse(links[i], parser_alloc, LENGTH(parser_alloc)));
		TEST_ASSERT(begin_paragraph(&checker_buffer));
		TEST_ASSERT(begin_link(&checker_buffer));
		TEST_ASSERT(write_buffer(&checker_buffer, "example.com"));
		TEST_ASSERT(end_link(&checker_buffer));
		TEST_ASSERT(end_paragraph(&checker_buffer));
		TEST_CHECK(strcmp(parser_alloc, checker_alloc) == 0);
		clear_buffer(&checker_buffer);
	}
}

int test_beginning_single_link(char *parser_alloc, int length_parser_alloc, struct Buffer *checker_buffer) {
	char *mixed_link = ">example.com lorem ipsum";

	TEST_ASSERT(string_parse(mixed_link, parser_alloc, length_parser_alloc));
	TEST_ASSERT(begin_paragraph(checker_buffer));
	TEST_ASSERT(begin_link(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, "example.com"));
	TEST_ASSERT(end_link(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, " lorem ipsum"));
	TEST_ASSERT(end_paragraph(checker_buffer));
	return strcmp(parser_alloc, checker_buffer->buffer) == 0;
}

int test_middle_single_link(char *parser_alloc, int length_parser_alloc, struct Buffer *checker_buffer) {
	char *mixed_link = "lorem >example.com ipsum";

	TEST_ASSERT(string_parse(mixed_link, parser_alloc, length_parser_alloc));
	TEST_ASSERT(begin_paragraph(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, "lorem "));
	TEST_ASSERT(begin_link(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, "example.com"));
	TEST_ASSERT(end_link(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, " ipsum"));
	TEST_ASSERT(end_paragraph(checker_buffer));
	return strcmp(parser_alloc, checker_buffer->buffer) == 0;
}

int test_end_single_link(char *parser_alloc, int length_parser_alloc, struct Buffer *checker_buffer) {
	char *mixed_link  = "lorem ipsum\n>example.com\n";

	TEST_ASSERT(string_parse(mixed_link, parser_alloc, length_parser_alloc));
	TEST_ASSERT(begin_paragraph(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, "lorem ipsum\n"));
	TEST_ASSERT(begin_link(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, "example.com"));
	TEST_ASSERT(end_link(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, "\n"));
	TEST_ASSERT(end_paragraph(checker_buffer));
	return strcmp(parser_alloc, checker_buffer->buffer) == 0;
}

int test_multi_link(char *parser_alloc, int length_parser_alloc, struct Buffer *checker_buffer) {
	char *mixed_link  = "> example.com> example.com lorem ipsum\n>example.com";

	TEST_ASSERT(string_parse(mixed_link, parser_alloc, length_parser_alloc));
	TEST_ASSERT(begin_paragraph(checker_buffer));
	TEST_ASSERT(begin_link(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, "example.com"));
	TEST_ASSERT(end_link(checker_buffer));
	TEST_ASSERT(begin_link(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, "example.com"));
	TEST_ASSERT(end_link(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, " lorem ipsum\n"));
	TEST_ASSERT(begin_link(checker_buffer));
	TEST_ASSERT(write_buffer(checker_buffer, "example.com"));
	TEST_ASSERT(end_link(checker_buffer));
	TEST_ASSERT(end_paragraph(checker_buffer));
	return strcmp(parser_alloc, checker_buffer->buffer) == 0;
}

void test_parse_mixed_links(void) {
	char parser_alloc[256];
	char checker_alloc[256];
	struct Buffer checker_buffer;

	init_buffer(&checker_buffer, checker_alloc, LENGTH(checker_alloc));
	TEST_CHECK(test_beginning_single_link(parser_alloc, LENGTH(parser_alloc), &checker_buffer));
	clear_buffer(&checker_buffer);
	TEST_CHECK(test_middle_single_link(parser_alloc, LENGTH(parser_alloc), &checker_buffer));
	clear_buffer(&checker_buffer);
	TEST_CHECK(test_end_single_link(parser_alloc, LENGTH(parser_alloc), &checker_buffer));
	clear_buffer(&checker_buffer);
	TEST_CHECK(test_multi_link(parser_alloc, LENGTH(parser_alloc), &checker_buffer));
	clear_buffer(&checker_buffer);
}
