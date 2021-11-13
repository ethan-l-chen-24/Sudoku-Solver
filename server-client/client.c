/* 
 * inclient - an example Internet client.
 *
 * Makes a connection to the given host/port and sends and receives sudoku messages
 * through that socket.
 * 
 * usage: inclient hostname port
 * 
 * David Kotz, 1987, 1992, 2016
 * Adapted from Figure 7a in Introductory 4.3bsd IPC, PS1:7-15.
 *
 * updated by Xia Zhou, August 2016, 2017, 2018
 * updated by Temi Prioleau, 2020
 * 
 * updated by Ethan Chen, Jeffrey Jiang, and Bansharee Ireen, November 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	      // read, write, close
#include <string.h>	      // memcpy, memset
#include <netdb.h>	      // socket-related structures

/**************** file-local constants ****************/
#define BUFSIZE 1024 // read/write buffer size

/**************** main() ****************/
int
main(const int argc, char * argv[]) {
    char * program; // this program's name
    char * hostname; // server hostname
    int port; // server port

    // 0. Check arguments
    program = argv[0];
    if (argc != 3) {
        fprintf(stderr, "usage: %s hostname port\n", program);
        exit(1);
    } else {
        hostname = argv[1];
        port = atoi(argv[2]);
    }

    // 1. Create socket
    int comm_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (comm_sock < 0) {
        perror("opening socket");
        exit(2);
    }

    // 2. Initialize the fields of the server address
    struct sockaddr_in server; // address of the server
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    // Look up the hostname specified on command line
    struct hostent * hostp = gethostbyname(hostname); // server hostname
    if (hostp == NULL) {
        fprintf(stderr, "%s: unknown host '%s'\n", program, hostname);
        exit(3);
    }
    memcpy( & server.sin_addr, hostp -> h_addr_list[0], hostp -> h_length);

    // 3. Connect the socket to that server   
    if (connect(comm_sock, (struct sockaddr * ) & server, sizeof(server)) < 0) {
        perror("connecting stream socket");
        exit(4);
    }

    // print user options
    printf("Connected!\n");
    printf("Type \"create\" to request a sudoku board from the server\n");
    printf("Type \"solve\" to solve your current sudoku board\n");
    printf("Type \"print\" to print the current solved or unsolved sudoku board\n\n");

    // 4. Read content from stdin (file descriptor = 0) and write to socket
    char buf[BUFSIZE];
    int bytes_read; // #bytes read from socket
    memset(buf, 0, BUFSIZE); // clear up the buffer
    do {
        if ((bytes_read = read(0, buf, BUFSIZE - 1)) < 0) {
            perror("reading from stdin");
            exit(5);
        } else {
            // try writing on the socket
            if (write(comm_sock, buf, bytes_read) < 0) {
                perror("writing on stream socket");
                exit(6);
            }
            memset(buf, 0, BUFSIZE);

            // try reading from the socket
            if ((bytes_read = read(comm_sock, buf, BUFSIZE - 1)) < 0) {
                perror("reading from stdin");
                exit(5);
            } else if (bytes_read == 0) {
                printf("Ending connection\n");
            } else {
                // if there is something, print it to stdout
                printf("%s", buf);
            }
        }
        fflush(stdout); // flush to ensure printing
    } while (bytes_read != 0);

    close(comm_sock);

    return 0;
}