.POSIX:
.PHONY: all clean test

LIBDIR=..
UTESTDIR=acutest

.c:
	export PKG_CONFIG_PATH=$(LIBDIR) &&\
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

RM      = rm -f
LDLIBS = $(LIBDIR)/libnote.a
LDLIBS += `pkg-config note --libs --static`
CFLAGS  = -Wall -Wextra
CFLAGS += -g
CFLAGS += -D_POSIX_C_SOURCE=200809L
CFLAGS += -I$(UTESTDIR)/include/
CFLAGS += -I$(LIBDIR)

test: test_all
	./test_all

test_all: test_all.c test_test.c test_buffer.c test_parse.c

clean:
	$(RM) *.o
	$(RM) test*[!ch]
