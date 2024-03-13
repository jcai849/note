PROG = note

RM = rm -f
CFLAGS = -Wall -Wextra -g -O2 -ansi -Wpedantic -D_POSIX_C_SOURCE=200112L
LDLIBS= `pkg-config libgvc --libs` -lfl
YFLAGS = -dtvy

${PROG}: y.tab.c lex.yy.c main.c graph.c
	$(CC) $(CFLAGS) y.tab.c lex.yy.c main.c graph.c $(LDLIBS) -o ${PROG}
main.c: y.tab.h
lex.yy.c: ${PROG}.l y.tab.h
	${LEX.l} ${PROG}.l
y.tab.c y.tab.h: ${PROG}.y 
	${YACC.y} ${PROG}.y
clean:
	${RM} lex.yy.c
	${RM} y.output
	${RM} y.tab.c
	${RM} y.tab.h
