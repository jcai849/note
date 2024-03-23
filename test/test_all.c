#include "acutest.h"
#include "note.h"

void test_testing(void) {
	TEST_CHECK(1);
}

void test_parse_tree(void) {
	TEST_CHECK(string_parse("") == 0);
}

void test_multiple_parses(void) {
	TEST_CHECK(string_parse("") == 0);
	TEST_CHECK(string_parse("") == 0);
	TEST_CHECK(string_parse("") == 0);
}

/* FEATURES
 *
 * string_parse returns a parse tree
 * sring_parse of text with no link returns a parse tree with a single node
 * string_parse of text with no link returns a parse tree with original text
 * sring_parse of text with link only returns a parse tree with a single node
 * string_parse of text with link only returns a parse tree with link text
 * string_parse of text with link inside returns a parse tree where all links are given (link at beginning, middle, and end of text)
 *
*/

TEST_LIST = {
   { "the testing framework is working", test_testing },
   { "the parse_tree() performs a parse", test_parse_tree },
   { "multiple parses are allowed for", test_multiple_parses },
   { NULL, NULL }     /* zeroed record marking the end of the list */
};
