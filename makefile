.POSIX:
.PHONY: all lib test clean

PROG = note

RM       = rm -f
CFLAGS   = -Wall -Wextra
CFLAGS  += -g
CFLAGS  += -D_POSIX_C_SOURCE=200809L
LDFLAGS  =  `pkg-config note --libs --static`
YFLAGS   = -yd

.y.c:
	export POSIXLY_CORRECT=1 &&\
	$(YACC) $(YFLAGS) $<
	mv y.tab.c $@

all: lib test

lib: libnote.a
libnote.a: libnote.a(scanner.o parser.o parse-tree.o)
scanner.o: y.tab.h
y.tab.h: parser.o
parser.o: note.h

test: lib
	cd test && $(MAKE) test

clean:
	$(RM) ${PROG}
	$(RM) y.tab.h
	$(RM) *.o
	$(RM) *.a
	cd test && $(MAKE) clean
