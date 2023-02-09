[LibIPC][libipc] C examples: `pong` and `pongd` (simple service and its client, just echoing received messages).
Implementations are straightforward.

## Build

`make`

Some options are available, such as static builds.

```sh
make STATIC=1 # Build static executables.
```

## Usage

```sh
./zig-out/bin/pongd # run the service
./zig-out/bin/pong  # run the client
```

## LICENSE

ISC

[libipc]: https://git.baguette.netlib.re/Baguette/libipc
