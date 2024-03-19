%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char *

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
