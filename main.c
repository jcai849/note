#include "y.tab.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-p") == 0)
        yydebug = 1;
    yyparse();
    return 0;
}
