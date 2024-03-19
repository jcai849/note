%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char *

int yylex(void);
%}

%token <string> LINK TEXT

%%

document: 
	/* empty */
        | document link
        | document text
        ;
link:	LINK
	;
text:	TEXT
	;
