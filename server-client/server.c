/* 
 * inserver - an example Internet server.
 *
 * This program accepts connections forever in an infinite loop.
 * 
 * usage: inserver-fork
 *  and ctrl-C to exit.
 *
 * David Kotz, 1987, 1992, 2016
 * Adapted from Figure 7b in Introductory 4.3bsd IPC, PS1:7-16,17.
 *
 * updated by Xia Zhou, August 2016, 2017, 2018
 * updated by Temi Prioleau, 2020
 * 
 * updated by Ethan Chen, Jeffrey Jiang, and Bansharee Ireen, November 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>        // bool type
#include <string.h>         // memcpy, memset
#include <unistd.h>         // read, write, close, fork
#include <arpa/inet.h>      // socket-related calls
#include <signal.h>       // wait() and waitpid(), signal()
#include <math.h>
#include "creator.h"
#include "solver.h"
#include "../sudoku/sudokuTable.h"

/**************** file-local constants ****************/
#define SERV_PORT 3000 // server port number 
#define LISTEN_BACKLOG 5 // number of connections to keep waiting
#define BUFSIZE 1024 // read/write buffer size

// function prototypes
sudokuTable_t * create(int comm_sock);
void print(sudokuTable_t * sudoku, int comm_sock);
void solve(sudokuTable_t * sudoku, int comm_sock);

/**************** main() ****************/
int main(const int argc, char * argv[]) {
    int list_sock, comm_sock;
    struct sockaddr_in server; // server address
    char buf[BUFSIZE]; // buffer for reading data from socket
    int bytes_read; // #bytes read from socket

    signal(SIGCHLD, SIG_IGN); // reap zombie processes automatically

    // 1. Create socket on which to listen (file descriptor)
    list_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (list_sock < 0) {
        perror("opening socket stream");
        exit(1);
    }

    // 2. Initiate the fields of the server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERV_PORT);

    // 3. bind the socket to the given server address
    if (bind(list_sock, (struct sockaddr * ) & server, sizeof(server))) {
        perror("binding socket name");
        exit(2);
    }
    printf("Listening at port %d\n", ntohs(server.sin_port));
    printf("To find your MacOS IP address, ifconfig | grep 'inet '\n");

    // 4. Start accepting connections, and allow one connection at a time
    listen(list_sock, LISTEN_BACKLOG);
    while (true) {
        // accept connection and receive communication socket (file descriptor)
        comm_sock = accept(list_sock, 0, 0);
        if (comm_sock == -1)
            perror("accept");
        else {
            // start a new process to handle the new client
            if (fork()) {
                // parent process
                close(comm_sock);
            } else {
                // child process
                close(list_sock);

                printf("Connection started\n\n");
                sudokuTable_t * sudoku = NULL;

                do {
                    memset(buf, 0, sizeof(buf)); // fill buffer with nulls
                    if ((bytes_read = read(comm_sock, buf, BUFSIZE - 1)) < 0)
                        perror("reading stream message");
                    if (bytes_read == 0)
                        printf("Ending connection\n");
                    else {

                        /********* MESSAGE RECEIVED FROM CLIENT ************/

                        printf("Received %s", buf);

                        // handle input
                        if (strcmp(buf, "create\n") == 0) { // create mode
                            if (sudoku != NULL) sudokuTable_delete(sudoku);
                            sudoku = create(comm_sock);
                        } else if (strcmp(buf, "solve\n") == 0) { // solve mode
                            solve(sudoku, comm_sock);
                        } else if (strcmp(buf, "print\n") == 0) { // print mode
                            print(sudoku, comm_sock);
                        } else { // invalid input
                            if (write(comm_sock, "\tbad input, try again\n", 25) < 0) {
                                perror("writing on stream socket");
                                exit(6);
                            }
                        }
                    }
                } while (bytes_read != 0);
                close(comm_sock);

                // end the thread and delete the sudoku board
                printf("Connection ended\n");
                if (sudoku != NULL) sudokuTable_delete(sudoku);
                exit(0);
            }
        }

    }

    close(list_sock);
    /* Note that if the server doesn't explicitly exit or close the socket,
     * the socket will be closed when the program is killed or terminates. */
}

/***************** create ******************/
/*
 * creates a sudoku board on server, sends message to client
 */
sudokuTable_t * create(int comm_sock) {

    // create the sudoku board
    sudokuTable_t * sudoku = createUniqueTable(37, 9);

    // write message to the client
    if (write(comm_sock, "\tsudoku table created\n", 22) < 0) {
        perror("writing on stream socket");
        exit(6);
        return NULL;
    }

    // print on server stdout
    printf("Created sudoku table: \n");
    sudokuTable_print(stdout, sudoku);
    printf("\n");
    return sudoku;
}

/***************** create ******************/
/*
 * solves the client's sudoku board on the server, sends message to client
 */
void solve(sudokuTable_t * sudoku, int comm_sock) {

    // check if the board has yet been created
    if (sudoku == NULL) {
        printf("\tcan't solve, null\n");
        if (write(comm_sock, "\tcan't solve a sudoku table that hasn't been created!\n", 100) < 0) {
            perror("writing on stream socket");
            exit(6);
        }
        return;
    }

    // solve the sudoku table
    solveSudoku(sudoku, 1, 9);

    // write message to client
    if (write(comm_sock, "\tsolved sudoku table\n", 21) < 0) {
        perror("writing on stream socket");
        exit(6);
    }

    // print on server stdout
    printf("\tSolved sudoku table: \n");
    sudokuTable_print(stdout, sudoku);
    printf("\n");
}

/***************** print ******************/
/**
 * formats a string with the sudoku table format
 * and sends it to the client
 */
void print(sudokuTable_t * sudoku, int comm_sock) {

    // check if the board has yet been created 
    if (sudoku == NULL) {
        printf("\tcan't print, null\n");
        if (write(comm_sock, "\tcan't print a sudoku table that hasn't been created!\n", 100) < 0) {
            perror("writing on stream socket");
            exit(6);
        }
        return;
    }

    // get necessary numbers from server and client
    int dimension = sudokuTable_dimension(sudoku);
    int sqrtDimension = sqrt(dimension);

    // create the string with a large initial buffer size
    char nums[BUFSIZE];
    sprintf(nums, "\t-");

    // create the string
    for (int i = 0; i < sqrtDimension; i++) {
        for (int j = 0; j < sqrtDimension; j++) {
            strncat(nums, "---\0", 4);
        }
        strncat(nums, "--\0", 3);
    }
    strncat(nums, "\n\t\0", 2);
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            if (col % 3 == 0) {
                strncat(nums, "| \0", 3);
            }
            int val = sudokuTable_get(sudoku, row, col);
            char temp[13];
            sprintf(temp, "%2d ", val);
            strncat(nums, temp, 13);
        }
        strncat(nums, "| \0", 3);

        if (((row + 1) % 3) == 0) {
            strncat(nums, "\n\t-\0", 3);
            for (int i = 0; i < sqrtDimension; i++) {
                for (int j = 0; j < sqrtDimension; j++) {
                    strncat(nums, "---\0", 3);
                }
                strncat(nums, "--\0", 2);
            }
            if (row != 8) {
                strncat(nums, "\n\t\0", 2);
            } else {
                strncat(nums, "\n\0", 2);
            }
        } else {
            strncat(nums, "\n\t\0", 2);
        }
    }

    // write the string to the client
    if (write(comm_sock, nums, 500) < 0) {
        perror("writing on stream socket");
        exit(6);
    }

    // print to server's stdout
    printf("\tprinted table\n");
}