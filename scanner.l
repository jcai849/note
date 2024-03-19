%option nounput
%option noinput

%{

#include <string.h>

#define YYSTYPE char *
#include "y.tab.h"
%}

LINK		>
TEXT		[^>]+

%%

{LINK}[[:blank:]]*	{ yylval = strdup(yytext); return LINK; }
{TEXT}			{ yylval = strdup(yytext); return TEXT; }
