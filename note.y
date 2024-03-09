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
	Agnode_t *self_node;
	self_node = agnode(graph, "self", TRUE);
	Agnode_t *ref_node = agnode(graph, $2, 1);
	agedge(graph, self_node, ref_node, 0, 1);
	free($2);
};
text:
      TEXT
    | LINK TEXT
    ;
