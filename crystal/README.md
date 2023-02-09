Crystal LibIPC examples, using [libipc bindings shard][bindings].

## Build

```sh
# Compiles all examples.
make
```

Currently there are 2 examples:
- pongd (server): repeating every message
- pong (client): sending a message to the pong service and waiting for response

## Usage

```sh
# Run the service
./bin/pongd # run the service
./bin/pong  # run the client
```

## LICENSE

ISC

[bindings]: https://git.baguette.netlib.re/Baguette/ipc.cr
