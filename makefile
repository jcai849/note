PROG=note

RM=rm -f
CFLAGS = -g
LFLAGS = -i
YFLAGS = -dtv

${PROG}: y.tab.c lex.yy.c main.c
	${LINK.c} y.tab.c lex.yy.c main.c -o ${PROG}
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
