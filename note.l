/*%option main debug*/
%option nounput
%option noinput

%{
#include <string.h>
#include "y.tab.h"
%}

%x NAME

LINK	>
WORD	[[:graph:]]+
NONWORD [^[:graph:]]
TEXT	[^>]+

%%

{LINK}		{ BEGIN(NAME); yylval.string = strdup(yytext); return LINK; }
<NAME>{WORD}	{ BEGIN(0); yylval.string = strdup(yytext); return LINK_ADDR; }
<NAME>{NONWORD}	{ BEGIN(0); yylval.string = strdup(yytext); return TEXT; }
{TEXT}		{ yylval.string = strdup(yytext); return TEXT; }
