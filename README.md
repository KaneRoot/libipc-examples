[LibIPC][libipc] examples in many languages:
- C
- Zig
- Crystal

and soon even more!

# Build

Just type `make` in the right directory.

# Some makefile utilities

All examples' makefiles include `mk/makefile.utils`.
Go have a look.
You'll be able to ask for a static build, run an application with valgrind with many options, and so on.
For example: `make STATIC=1 build` will compile your example as a static executable (in all languages).

[libipc]: https://git.baguette.netlib.re/Baguette/libipc
