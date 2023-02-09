CC      ?= cc
USR_LDFLAGS ?=
LDFLAGS ?= -lipc
LDFLAGS += $(USR_LDFLAGS)
LDFLAGS += $(STATIC_BUILD)
CFLAGS  ?= -Wall -Wextra

all: build

include ../mk/makefile.utils

BINS = pong pongd
build: $(BINS)

$(BINS):
	$(CC) -o $@ $@.c $(CFLAGS) $(LDFLAGS)

clean:
	rm $(BINS) 2>/dev/null

# You can add your specific instructions there.
-include makefile.user
