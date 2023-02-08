CC      ?= cc
LDFLAGS ?= -lipc

include makefile.valgrind

all: build

BINS = pong pongd
build: $(BINS)

$(BINS):
	$(CC) -o $@ $@.c $(LDFLAGS)

clean:
	rm $(BINS) 2>/dev/null

# You can add your specific instructions there.
-include makefile.user
