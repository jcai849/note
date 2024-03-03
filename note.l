%{
#include <stdio.h>
%}

%x NAME

LINK	>
WORD	[[:graph:]]*

%%

LINK		{ printf("LINK: %s\n", yytext); BEGIN(NAME); }
<NAME>{WORD}	{ printf("LINK_ADDR: %s\n", yytext); BEGIN(0); }
[^{LINK}]*	{ printf("TEXT: %s\n", yytext); }

%%

int main(int argc, char *argv[])
{
        ++argv; --argc;  /* skip over program name */
        if (argc > 0)
                yyin = fopen(argv[0], "r");
        else
                yyin = stdin;

        yylex();
	printf("\n");
}
