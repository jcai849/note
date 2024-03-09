%{
#include <stdio.h>
#include <string.h>
#include "note.h"
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
link: LINK LINK_ADDR {
	Agnode_t *m = agnode(g, $2, 1);
	agedge(g, n, m, 0, 1);
	free($2);
};
text:
      TEXT
    | LINK TEXT
    ;
