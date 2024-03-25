.POSIX:
.PHONY: all lib test clean

PROG = note

RM       = rm -f
CFLAGS   = -Wall -Wextra
CFLAGS  += -g
CFLAGS  += -D_POSIX_C_SOURCE=200809L
LDFLAGS  =  `pkg-config note --libs --static`
#LFLAGS   = -d

all: lib test

lib: libnote.a
libnote.a: libnote.a(scanner.o buffer.o generator.o)
scanner.o: note.h buffer.h generator.h
generator.o: buffer.h
buffer.o: buffer.h

test: lib
	cd test && $(MAKE) test

clean:
	$(RM) ${PROG}
	$(RM) *.o
	$(RM) *.a
	cd test && $(MAKE) clean
