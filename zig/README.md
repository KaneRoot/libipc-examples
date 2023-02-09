Zig [LibIPC][libipc] examples:
`pong` and `pongd` (as you find in all other examples).
`tcpd` and `ipcd`, to make any LibIPC application network-ready.
Documentation will come soon for these.

## Build

```sh
# Compiles all examples.
make
```

Several options are available.

```sh
# Compiles all examples.
make STATIC=1 # Build static executables.
make ZIG_OPTIM=ReleaseSmall # Build small executables.
```

Read the makefile.

## Usage

```sh
./zig-out/bin/pongd # run the service
./zig-out/bin/pong  # run the client
```

## LICENSE

ISC

[libipc]: https://git.baguette.netlib.re/Baguette/libipc
