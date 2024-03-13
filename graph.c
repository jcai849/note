#include <graphviz/gvc.h>
#include "note.h"

Agraph_t *graph;

void init_graph(void) {
	graph = agopen("G", Agstrictdirected, NULL);
}
void write_graph(void) {
	agwrite(graph, stdout);
}
void close_graph(void) {
	agclose(graph);
}
void add_link_to_graph(char *tail_name, char *head_name) {
	Agnode_t *head, *tail;

        tail = agnode(graph, tail_name, TRUE);
        head = agnode(graph, head_name, 1);
        agedge(graph, tail, head, 0, 1);
}
