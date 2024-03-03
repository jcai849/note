%{
#include <stdio.h>
#include <string.h>

int yylex(void);
void yyerror (char const *s) {
	fprintf (stderr, "%s\n", s);
}
%}

%union { char * string; }
%token <string> LINK LINK_ADDR TEXT

%%

link: LINK LINK_ADDR;


%%

int main(int argc, char *argv[]) {
    /* Enable parse traces on option -p. */
    if (argc == 2 && strcmp(argv[1], "-p") == 0)
        yydebug = 1;
    yyparse();
    return 0;
}
