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
int output_begin_link(void)      { return begin_link(&output_buffer); }
int output_end_link(void)        { return end_link(&output_buffer); }

%}

%x PARAGRAPH HEADING LIST_ITEM KV_LIST
%x LINK

/* blocks */
HEADING_MARKER          =
LIST_ITEM_MARKER        -
ORDERED_LIST_MARKER     1\.
KV_LIST_KEY_BEGIN       \[
KV_LIST_KEY_END         \[
NOTE_BEGIN              \[?NOTE\]?|:?
PARAGRAPH_MARKER        .

BLOCK_END	        \n[[:blank:]]*\n

LINK_BEGIN              >[[:blank:]]*
ALT_LINK_BEGIN          >>[[:blank:]]*
TRANSCLUSION_BEGIN      >+
/* ^ bring in as <div> with identifier */
EMBEDDED_TRANSCLUSION_BEGIN >\|
EMBEDDED_TRANSCLUSION_END    \|
LINK_END                >|[[:space:]]
ANCHOR_BEGIN            @

ADDRESS                 [^\\[:space:]>]*

STRONG                  \*
ITALIC                  ~
SUPERSCRIPT             \^
SUBSCRIPT               _
VARIABLE                \|
TEXT                    [^\n>]*
/* TEXT	                [^*^_|\n\\>@]* */

QUOTE_QUOTE             \\\\
QUOTE_LINK_BEGIN_PRE    \\>
QUOTE_LINK_BEGIN_POST   >\n
QUOTE_LINK_END          \\[[:blank:]] 
QUOTE_HEADING_MARKER    \\=
QUOTE_LIST_ITEM_MARKER  \\-
/* etc... */
QUOTE_CATCH             \\

%%
	int RET = 0;

<INITIAL>[[:space:]]*
<INITIAL>{PARAGRAPH_MARKER} { CHECK(output_begin_paragraph());
                              yyless(0); BEGIN(PARAGRAPH);}

<PARAGRAPH>{LINK_BEGIN} { output_begin_link(); RET = PARAGRAPH; BEGIN(LINK); }
<PARAGRAPH>{QUOTE_LINK_BEGIN_PRE}  { CHECK(wo(yytext+1)); }
<PARAGRAPH>{QUOTE_LINK_BEGIN_POST} { CHECK(wo(yytext)); }
<PARAGRAPH>{TEXT}       |
<PARAGRAPH>\n           CHECK(wo(yytext));
<PARAGRAPH><<EOF>>      |
<PARAGRAPH>{BLOCK_END}  { CHECK(output_end_paragraph()); BEGIN(INITIAL); }

<LINK>{ADDRESS}         { CHECK(wo(yytext)); }
<LINK>{QUOTE_LINK_END}  { yyless(0); }
<LINK>{QUOTE_LINK_BEGIN_PRE} { CHECK(wo(">")); }
<LINK>{QUOTE_QUOTE}     |
<LINK>{QUOTE_CATCH}     { CHECK(wo("\\")); }
<LINK><<EOF>>           |
<LINK>{LINK_END}        { output_end_link(); yyless(0); BEGIN(RET); }

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
