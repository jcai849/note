.POSIX:
.PHONY: all lib test clean tags debug release

PROG = note

RM       = rm -f
CFLAGS   = -Wall -Wextra
CFLAGS  += -std=c99 -pedantic
CFLAGS  += -g
CFLAGS  += -fanalyzer 
LDFLAGS =  `pkg-config note --libs --static`

all: lib

debug: LFLAGS += -d
debug: all

release: CFLAGS += O3
release: all

lib: libnote.a
libnote.a: libnote.a(scanner.o buffer.o generator.o)
scanner.o: CFLAGS += -D_POSIX_C_SOURCE
scanner.o: scanner.l note.h buffer.h generator.h
generator.o: generator.c buffer.h
buffer.o: buffer.c buffer.h

test: CFLAGS += -fsanitize=address,undefined
test: lib
	cd test && $(MAKE) test

clean:
	$(RM) ${PROG}
	$(RM) *.o
	$(RM) *.a
	cd test && $(MAKE) clean

tags:
	ctags -R
