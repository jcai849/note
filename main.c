#include <string.h>
#include <stdio.h>
#include "y.tab.h"
#include "note.h"

Agraph_t *g;
Agnode_t *n;

int main(int argc, char *argv[]) {
	if (argc == 2 && strcmp(argv[1], "-p") == 0) yydebug = 1;
	g = agopen("G", Agstrictdirected, NULL);
	n = agnode(g, "self", TRUE);
	yyparse();
	agwrite(g, stdout);
	return 0;
}
