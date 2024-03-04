%{
#include <stdio.h>
#include <string.h>
#define YYDEBUG 1
int yylex(void);
void yyerror (char const *s) { fprintf (stderr, "%s\n", s); }
%}
%union { char * string; }
%token <string> LINK LINK_ADDR TEXT

%%

document: 
	/* empty */
        | document link
        | document text
        ;
link: LINK LINK_ADDR ;
text:
      TEXT
    | LINK TEXT
    ;
