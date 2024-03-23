%{

#include <stdio.h>
#include <string.h>
#include "note.h"

void yyerror (char const *s) { fprintf (stderr, "%s\n", s); }

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

%%

int string_parse(char *s) {
        string_buffer_create(s);
        yyparse();
        string_buffer_delete();
        return 0;
}

