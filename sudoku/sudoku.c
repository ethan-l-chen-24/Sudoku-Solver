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
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include "creator.h"
#include "solver.h"
#include "sudokuTable.h"


// function prototypes

void validateParam(char* mode, char* difficulty);
void createTable(char* difficulty);
void solveTable();
int fileno(FILE *stream);

/**************** validateParam ********************/
/*
 *
*/
void validateParam(char* mode, char* difficulty) {
    if (strcmp(mode, "create") != 0 && strcmp(mode, "solve") != 0) {
        fprintf(stderr, "Please select a valid mode: create or solve.\n");
        exit(1);
    }

    if (strcmp(difficulty, "easy") != 0 && strcmp(difficulty, "hard") != 0) {
        fprintf(stderr, "Please select a valid level of difficulty: easy or hard.\n");
        exit(2);
    }
}

#ifndef UNITTEST

/**************** main ********************/
/*
 *
*/
int main(const int argc, char* argv[]) {
    srand(time(NULL));
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
        // pass difficulty parameter to creator
        createTable(difficulty);
        
    } else {
        solveTable();
    }
}

#endif

/**************** createTable ********************/
/*
 *
*/
void createTable(char* difficulty) {
    // generate a table
    if(difficulty == NULL) return;

    // generate sudoku tables based on difficulty
    sudokuTable_t* sudoku;
    if(strcmp(difficulty, "easy") == 0) {
        sudoku = generateUniqueTable(37);
    } else {
        sudoku = generateUniqueTable(25);
    }

    // print it out
    if (isatty(fileno(stdout))) { // print out generated line only if stdout is not a file
        printf("Generated Table, %s difficulty: \n", difficulty);
    }
    sudokuTable_print(sudoku, true);
}

/**************** solveTable ********************/
/*
 *
*/
void solveTable() {
    // generate a table
    sudokuTable_t* sudoku = sudokuTable_load(stdin, 9);
    if(sudoku == NULL) return;

    // print the original board
    printf("Original Board: \n");
    sudokuTable_print(sudoku, true);

    // solve the board
    if(!solveSudoku(sudoku, 1)) {
        fprintf(stderr, "Could not solve board\n");
        return;
    }

    // print the solved board
    printf("Solved: \n");
    sudokuTable_print(sudoku, true);
}