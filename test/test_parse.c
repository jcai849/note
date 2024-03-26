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
		string_parse(single_p[i], parser_alloc, LENGTH(parser_alloc));
		begin_paragraph(&checker_buffer);
		write_buffer(&checker_buffer, single_p[0]);
		end_paragraph(&checker_buffer);
		TEST_CHECK(strcmp(parser_alloc, checker_alloc) == 0);
		clear_buffer(&checker_buffer);
	}

	TEST_CASE("single paragraph trailing newline");
	string_parse(single_p_trailing_n, parser_alloc, LENGTH(parser_alloc));
	begin_paragraph(&checker_buffer);
	write_buffer(&checker_buffer, single_p_trailing_n);
	end_paragraph(&checker_buffer);
	TEST_CHECK(strcmp(parser_alloc, checker_alloc) == 0);
	clear_buffer(&checker_buffer);
}

void test_parse_multi_paragraph(void) {
	char parser_alloc[30];
	char checker_alloc[30];
	struct Buffer checker_buffer;
	long unsigned int i = 0;
	char *multi_p[]  = { "\n\nLorem\n\nIpsum",
                             "\nLorem\n\nIpsum\n\n",
                             "\n\nLorem\n\nIpsum\n\n",
                             "\n\nLorem\n\nIpsum\n\n\n",
                             "\n\nLorem\n\n\nIpsum\n\n" };

	init_buffer(&checker_buffer, checker_alloc, LENGTH(checker_alloc));
	
	TEST_CASE("multi paragraph");
	for (i = 0; i < LENGTH(multi_p); i++) {
		string_parse(multi_p[i], parser_alloc, LENGTH(parser_alloc));
		begin_paragraph(&checker_buffer);
		write_buffer(&checker_buffer, "Lorem");
		end_paragraph(&checker_buffer);
		begin_paragraph(&checker_buffer);
		write_buffer(&checker_buffer, "Ipsum");
		end_paragraph(&checker_buffer);
		TEST_CHECK(strcmp(parser_alloc, checker_alloc) == 0);
		clear_buffer(&checker_buffer);
	}
}
