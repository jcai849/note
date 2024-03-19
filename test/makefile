.POSIX:
.PHONY: all clean test

.c:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

LIBDIR=..
UTESTDIR=acutest

RM      = rm -f
LDLIBS = $(LIBDIR)/libnote.a
CFLAGS  = -Wall -Wextra
CFLAGS += -g
CFLAGS += -D_POSIX_C_SOURCE=200809L
CFLAGS += -I$(UTESTDIR)/include/
CFLAGS += -I$(LIBDIR)

all: test_all

test: all
	./test_all

clean:
	$(RM) *.o
	$(RM) test_all
