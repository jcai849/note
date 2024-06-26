#include "test_test.c"
#include "test_buffer.c"
#include "test_parse.c"

TEST_LIST = {
	{ "the testing framework is working", test_testing },

	{ "write_buffer buffer element is equivalent to string less than buffer size", test_buffer_w_smaller_string },
	{ "write_buffer returns with nonzero if string is equal or greater than buffer size", test_buffer_w_larger_string },
	{ "multiple buffer writes are equivalent to the input strings", test_buffer_w_multiple_strings },
	{ "clearing the buffer works as expected", test_clear_buffer },

	{ "the string_parse() performs a parse", test_parse },
	{ "multiple parses are allowed for", test_multiple_parses },
	{ "parse with a string larger than buffer returns 0", test_parse_too_big },
	{ "string_parse of single paragraph text with no link creates appropriate paragraph blocks", test_parse_single_paragraph },
	{ "string_parse of multi paragraph text with no link creates appropriate paragraph blocks", test_parse_multi_paragraph },
	{ "string_parse of only link is equivalent to paragraph with link in it", test_parse_solo_link },
	{ "string_parse of links mixed with test is equivalent to paragraph with links and text in it", test_parse_mixed_links },
	{ "string_parse of paragraph with escaped links yields no links", test_escaped_links },
	{ "string_parse of links with escapes yields appropriate links", test_links_w_escapes },
	{ NULL, NULL }     /* zeroed record marking the end of the list */
};

/* FEATURES
*
* refactor:
	* condition stack
	* reentrant
	* replace string parse with yyin fmemopen
	* replace buffer w/ open_memstream; ECHO
	* file output
*
* simple transclusion
* transclusion of stdin
*
* refactor: incl. yacc & strdup
*
* transclusion with escapes
*
* graphviz of links
*
* latex
*
* full orthography
*
* celebrate
*
* generic link
*
* formatting element: headers
* formatting flag
*
* transclusion of other file formats:
*     build system: logging of dependencies, builds of dependencies
*
* anchor
*
* other formatting elements
*
*/
