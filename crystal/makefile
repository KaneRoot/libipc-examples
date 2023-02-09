# The following shows how to use a library that is not installed.
# Usage example: make LIBPATH=/tmp/libipc/zig-out/lib/ build run

LIBPATH ?=
LD_LIBRARY_PATH=LD_LIBRARY_PATH=$(LIBPATH)
CRYSTAL_LIBRARY_PATH=CRYSTAL_LIBRARY_PATH=$(LIBPATH)
CRYSTAL_BUILD_OPTIONS ?=
CRYSTAL_BUILD_OPTIONS += $(CRYSTAL_STATIC_BUILD)

LIBIPC_RUNDIR ?= /tmp/libipc-run

all: build
build: build-pongd build-pong
run: run-pongd

include ../mk/makefile.utils

build-pongd:
	$(CRYSTAL_LIBRARY_PATH) shards build pongd $(CRYSTAL_BUILD_OPTIONS)

run-pongd:
	rm $(LIBIPC_RUNDIR)/pong 2>/dev/null || true
	$(LD_LIBRARY_PATH) ./bin/pongd

build-pong:
	$(CRYSTAL_LIBRARY_PATH) shards build pong $(CRYSTAL_BUILD_OPTIONS)

run-pong:
	$(LD_LIBRARY_PATH) ./bin/pong
