# LibIPC examples

Crystal LibIPC examples, using [libipc bindings shard][bindings].

## Installation

```sh
# Compiles all examples.
shards build
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

# LICENCE

ISC

[bindings]: https://git.baguette.netlib.re/Baguette/ipc.cr
