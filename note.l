/*%option main debug*/
%option nounput
%option noinput

%{
#include <string.h>
#include "y.tab.h"
char *preproc(char *text, char character)
%}

%x IN_LINK

LINK		>
TEXT		[^>]+
SINGLE_QUOTED   \'([^\\'\n]|(\\\'))+\'
DOUBLE_QUOTED   \"([^\\"\n]|(\\\"))+\"
WORD	        ([^\\[:space:][:cntrl:]]|(\\[[:blank:]]))+

%%

{LINK}[[:blank:]]*	{ BEGIN(IN_LINK); yylval.string = strdup(yytext); return LINK; }
<IN_LINK>{WORD}		{ BEGIN(0); yylval.string = strdup(yytext); return LINK_ADDR; }
<IN_LINK>{SINGLE_QUOTED} { BEGIN(0); yylval.string = strdup(preproc(yytext, '\'')); return LINK_ADDR; }
<IN_LINK>{DOUBLE_QUOTED} { BEGIN(0); yylval.string = strdup(preproc(yytext, '"')); return LINK_ADDR; }
{TEXT}			{ yylval.string = strdup(yytext); return TEXT; }

%%

char *preproc(char *text, char character) {
/* remove backslash for escaped character */
/* remove first and last characters */
return &'a'
}
