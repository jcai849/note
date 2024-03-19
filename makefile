.POSIX:

PROG = note

RM = rm -f
CFLAGS = -Wall -Wextra
CFLAGS += -g
CFLAGS += -D_POSIX_C_SOURCE=200809L
LDLIBS = -lfl -ly			# Flex & yacc libraries
#LDLIBS += `pkg-config libgvc --libs`	# graphviz
YFLAGS = -y				# POSIX yacc
YFLAGS += -d				# Emit header

POSIXLY_CORRECT=1
export POSIXLY_CORRECT

all debug: libnote.a
libnote.a: libnote.a(scanner.o parser.o)
scanner.o: y.tab.h
y.tab.h: parser.o
parser.o: note.h

clean:
	${RM} ${PROG}
	${RM} y.tab.h
	${RM} *.o
