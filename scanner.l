%option nounput
%option noinput

%{

#include <string.h>
#include "note.h"
#include "buffer.h"
#include "generator.h"

/* yylex returns 1 on failure */
#define CHECK(x) if (!x) return 1

struct Buffer output_buffer;

/* "Write Out" */
size_t wo(char *yytext) { return write_buffer(&output_buffer, yytext);}
int output_begin_paragraph(void) { return begin_paragraph(&output_buffer); }
int output_end_paragraph(void)   { return end_paragraph(&output_buffer); }

%}

%s PARAGRAPH HEADING LIST_ITEM KV_LIST
%s LINK LINK_NAME

/* blocks */
HEADING_MARKER          =
LIST_ITEM_MARKER        -
ORDERED_LIST_MARKER     1\.
KV_LIST_KEY_BEGIN       \[
KV_LIST_KEY_END         \[
NOTE_BEGIN              \[?NOTE\]?|:?
PARAGRAPH_MARKER        .

BLOCK_END	        \n{2,}

LINK_BEGIN              >>
TRANSCLUSION_BEGIN      >+
/* bring in as <div> with identifier */
LINK_END                " "
LINK_CATCH              >
ANCHOR_BEGIN            @
/* also -- account for line ending in link end w/ yyless(1); */

STRONG                  \*
ITALIC                  ~
SUPERSCRIPT             \^
SUBSCRIPT               _
VARIABLE                \|
TEXT	                [^*^_|\n\\>@]*

QUOTE_QUOTE             \\\\
QUOTE_LINK_BEGIN        \\>
QUOTE_LINK_END          "\\ "
QUOTE_HEADING_MARKER    \\=
QUOTE_LIST_ITEM_MARKER  \\-
/* etc... */
QUOTE_CATCH             \\

%%

<INITIAL>[[:space:]]*

<INITIAL>{PARAGRAPH_MARKER} { BEGIN(PARAGRAPH);
                              CHECK(output_begin_paragraph());
                              CHECK(wo(yytext)); }

<PARAGRAPH>{TEXT}       |
<PARAGRAPH>\n           CHECK(wo(yytext));
<PARAGRAPH><<EOF>>      |
<PARAGRAPH>{BLOCK_END}  { BEGIN(INITIAL);
                          CHECK(output_end_paragraph()); }

%%

/* return 0 on failure */
int string_parse(char *in, char *out, int out_size) {
	YY_BUFFER_STATE input_buffer;

	init_buffer(&output_buffer, out, out_size);
	input_buffer = yy_scan_string(in);
	if (yylex()) return 0;
	yy_delete_buffer(input_buffer);
	return 1;
}
