all: build

update-libipc:
	git submodule update

ZIG_OPTS  ?=
ZIG_OPTIM ?= ReleaseSafe
build:
	zig build -Doptimize=$(ZIG_OPTIM) $(ZIG_OPTS)
