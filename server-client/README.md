# Final Project - Jeffrey Jiang, Bansharee Ireen, Ethan Chen
## Sudoku Solver Server-Client Module, CS50 Fall 2021

### server-client module

This is a module that runs a server-client interface as an extension to the default Sudoku project. It contains `server.c` and `client.c`

* `server.c` - initializes a server at `port 3000` that a client can connect to
* `client.c` - creates a new client and connects it to a port

### server.c

`server.c` can be run by first compiling and then running `./server`. This will open a server that will wait for clients to connect to it indefinitely, or until the program is exited. The server can, upon connections, receive messages from the client, in which each message will activate certain actions:

* create - create a sudoku board
* solve - solve the sudoku board 
* print - send the formatted sudoku board back to the client

Each thread/client will have its own sudoku board, therefore they can run concurrently and request actions from the server. Synchronization of methods is handled with _mutex locks_ in `../creator/creator.c` and `../solver/solver.c`

### client.c

`client.c` can be run by first compiling and then running `./client hostname port`. For the `plank` host, and for the default `port 3000`, this should always be run with `./client plank 3000`. The client will be able to send messages from stdin to the server and receive messages and print it to stdout.

### Assumptions

`server.c` and `client.c` both only implement the sudoku communication on a 9x9 board. Additionally, both files assume that `port 3000` is free to be connected to, otherwise errors may occur.

### Compilation

To compile, just call `make`. This will compile the server and client file and create the `./server` and `./client` executables.