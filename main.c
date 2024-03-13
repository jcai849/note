#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "y.tab.h"
#include "note.h"

int output_graph=0, output_html=1;

int main(int argc, char *argv[]) {
	extern char *optarg;
	extern int optind;
	int c; 
	static char usage[] = "%s [-hdg]\n";

	while ((c = getopt(argc, argv, "hdg")) != -1)
		switch (c) {
		case 'h':
			fprintf(stderr, usage, argv[0]);
			exit(EXIT_SUCCESS);
		case 'd':
			yydebug = 1;
			break;
		case 'g':
			output_graph = 1; output_html = 0;
			break;
		case '?':
			fprintf(stderr, usage, argv[0]);
			exit(EXIT_FAILURE);
		}
	
	init_graph();
	yyparse();
	if (output_graph) write_graph();
	close_graph();
	exit(EXIT_SUCCESS);
}
