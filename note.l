/*%option main debug*/
%option noyywrap
%option nounput
%option noinput

%{
#include <string.h>
#include "y.tab.h"
%}

%x NAME

LINK	>
WORD	[[:graph:]]*
TEXT	[^>]+

%%

{LINK}		{ BEGIN(NAME); yylval.string = strdup(yytext); return LINK;}
<NAME>{WORD}	{ BEGIN(0); yylval.string = strdup(yytext); return LINK_ADDR; }
TEXT		{ yylval.string = strdup(yytext); return TEXT; }
