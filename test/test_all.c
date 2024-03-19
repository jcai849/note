#include "acutest.h"
#include "note.h"

void test_testing(void) {
	TEST_CHECK(1);
}

void test_linking(void) {
	TEST_CHECK(hello_world());
}


/* FEATURES
 *
 * parse_tree returns a parse
 * string_parse returns a parse tree
 * sring_parse of text with no link returns a parse tree with a single node
 * string_parse of text with no link returns a parse tree with original text
 * sring_parse of text with link only returns a parse tree with a single node
 * string_parse of text with link only returns a parse tree with link text
 * string_parse of text with link inside returns a parse tree where all links are given (link at beginning, middle, and end of text)
 */

TEST_LIST = {
   { "acutest", test_testing },
   { "linking", test_linking },
   { NULL, NULL }     /* zeroed record marking the end of the list */
};
