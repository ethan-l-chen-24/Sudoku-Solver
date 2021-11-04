/*
 * sudoku.c - can either create or solve sudoku boards
 *
 * usage: ./sudoku mode difficulty
 * 
 * Bansharee Ireen, Ethan Chen, Jeffrey Jiang
 * Nov 4, 2021
 * 
 * CS50, Fall 2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "creator.h"
#include "solver.h"

void validateParam(char* mode, char* difficulty);
int createTable(char* difficulty);

void validateParam(char* mode, char* difficulty) {
    if (strcmp(mode, "create") != 0 && strcmp(mode, "solve") != 0) {
        fprintf(stderr, "Please select a valid mode: create or solve.\n");
        exit(1);
    }

    if (strcmp(mode, "easy") != 0 && strcmp(mode, "hard") != 0) {
        fprintf(stderr, "Please select a valid level of difficulty: easy or hard.\n");
        exit(2);
    }
}

int main(const int argc, const char* argv[]) {
    // for now, checks if number of command-line arguments is 3
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments. Usage: ./sudoku mode difficulty\n");
        return 1;
    }

    // validates the parameters
    validateParam(argv[1], argv[2]);
    char* mode = argv[1];
    char* difficulty = argv[2];

    // if the mode is to create
    if (strcmp(mode, "create") == 0) {
        // pass difficulty parameter to creater
        if (createTable(difficulty) != 0) {  // create returns 0 on error
            fprintf(stderr, "Error creating sudoku board.\n");
            return 2;
        }
    }

}

// creates the sudoku board
int createTable(char* difficulty) {
    // generate a basic table

    // if creating on easy mode
    if (strcmp(difficulty, "easy")) {

    }
    // if creating on hard mode
    else {

    }
}