#include <string.h>
#include <stdio.h>
#include "y.tab.h"
#include "note.h"

Agraph_t *graph;
Agnode_t *self_node;

int main(int argc, char *argv[]) {
	if (argc == 2 && strcmp(argv[1], "-p") == 0) yydebug = 1;
	graph = agopen("G", Agstrictdirected, NULL);
	yyparse();
	agwrite(graph, stdout);
	return 0;
}
