%option nounput
%option noinput

%{

#include <string.h>
#include "note.h"
#include "buffer.h"

struct Buffer output_buffer;

%}

LINK_BEGIN        >
LINK_END          ' '
LINK_QUOTE_END    "\\ "
QUOTE_LINK_BEGIN  "\\>"
QUOTE_QUOTE       \\\\
TEXT	          [^\\>]*

%%

{TEXT}			{ write_buffer(&output_buffer, yytext); }

%%

int string_parse(char *in, char *out, int out_size) {
	YY_BUFFER_STATE input_buffer;

	init_buffer(&output_buffer, out, out_size);
	input_buffer = yy_scan_string(in);
	yylex();
	yy_delete_buffer(input_buffer);
	return 0;
}
