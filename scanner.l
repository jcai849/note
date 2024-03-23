%option nounput
%option noinput

%{

#include <string.h>
#include "note.h"
#include "y.tab.h"

YY_BUFFER_STATE string_buffer;

int string_buffer_create(char *s) {
	string_buffer = yy_scan_string(s);
	return 0;
}

int string_buffer_delete(void) {
	yy_delete_buffer(string_buffer);
	return 0;
}

%}

LINK_BEGIN        >
LINK_END          ' '
LINK_QUOTE_END    "\\ "
QUOTE_LINK_BEGIN  "\\>"
QUOTE_QUOTE       \\\\
TEXT	          [^\\>]+

%%

{TEXT}			{ yylval = strdup(yytext); return TEXT; }
