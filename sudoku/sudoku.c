/*
 * sudoku.c - can either create or solve sudoku boards
 *
 * usage: ./sudoku mode difficulty [dimensions]
 * 
 * Bansharee Ireen, Ethan Chen, Jeffrey Jiang
 * Nov 4, 2021
 * 
 * CS50, Fall 2021
 */
#pragma GCC target("avx2") // optimization to increase speed of solving
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "creator.h"
#include "solver.h"
#include "sudokuTable.h"

// function prototypes

void validateParam(char* mode, char* difficulty);
void createTable(char* difficulty, int dimensions);
void solveTable(int dimensions);
int fileno(FILE* stream);

/**************** validateParam ********************/
/*
 * ensures that the inputted arguments are of the correct format
 */
void validateParam(char * mode, char * difficulty) {
    // check for proper mode input
    if (strcmp(mode, "create") != 0 && strcmp(mode, "solve") != 0) {
        fprintf(stderr, "Please select a valid mode: create or solve.\n");
        exit(1);
    }

    // check for proper difficulty input
    if (strcmp(difficulty, "easy") != 0 && strcmp(difficulty, "hard") != 0) {
        fprintf(stderr, "Please select a valid level of difficulty: easy or hard.\n");
        exit(2);
    }
}

void checkDim(int dimension) {
    // for now check that dimension is either 9 or 16
    if (dimension != 4 && dimension != 9 && dimension != 16) {
        fprintf(stderr, "Dimension must be a 4, 9, or 16.\n");
        exit(1);
    }
}

/**************** main ********************/
/*
 * validates arguments and then passes to create or solve depending on arguments
 */
int main(const int argc, char * argv[]) {
    srand(time(NULL));
    // for now, checks if number of command-line arguments is 3 or 4
    if (argc != 3 && argc != 4) {
        fprintf(stderr, "Incorrect number of arguments. Usage: ./sudoku mode difficulty [dimensions]\n");
        return 1;
    }

    // validates the parameters
    validateParam(argv[1], argv[2]);
    char* mode = argv[1];
    char* difficulty = argv[2];

    // set 9 as default dimensions
    int dimensions = 9;
    // update dimensions if argument was provided
    if (argc == 4) {
        int dim = atoi(argv[3]);
        // check if the dimension argument is valid
        checkDim(dim);
        dimensions = dim;
    }

    // if the mode is to create
    if (strcmp(mode, "create") == 0) {
        // pass difficulty parameter to creator
        createTable(difficulty, dimensions);
    } else {
        solveTable(dimensions);
    }
}

/**************** createTable ********************/
/*
 * creates a sudoku table and prints it to stdout
 */
void createTable(char * difficulty, int dimensions) {
    // create a table
    if (difficulty == NULL) {
        return;
    }
    // create sudoku tables based on difficulty
    sudokuTable_t * sudoku;
    if (strcmp(difficulty, "easy") == 0) {
        if (dimensions == 4) {
            sudoku = createUniqueTable(8, dimensions);
        } else if (dimensions == 9) {
            sudoku = createUniqueTable(37, dimensions);
        } else {
            sudoku = createUniqueTable(150, dimensions);
        }
    } else {
        if (dimensions == 4) {
            sudoku = createUniqueTable(4, dimensions);
        } else if (dimensions == 9) {
            sudoku = createUniqueTable(25, dimensions);
        } else {
            sudoku = createUniqueTable(135, dimensions);
        }
    }

    // print it out
    if (isatty(fileno(stdout))) { // print out created line only if stdout is not a file
        printf("created Table, %s difficulty: \n", difficulty);
    }
    sudokuTable_print(stdout, sudoku);
    sudokuTable_delete(sudoku);
}

/**************** solveTable ********************/
/*
 * loads a sudokuTable from stdin, solves it (if possible), and prints it to stdout
 */
void solveTable(int dimensions) {
    // create a table
    sudokuTable_t * sudoku = sudokuTable_load(stdin, dimensions);
    if (sudoku == NULL) {
        return;
    }
    // print the original board
    printf("Original Board: \n");
    sudokuTable_print(stdout, sudoku);

    // solve the board
    if (!solveSudoku(sudoku, 1, dimensions)) {
        fprintf(stderr, "Could not solve board\n");
        return;
    }

    // print the solved board
    printf("Solved: \n");
    sudokuTable_print(stdout, sudoku);
    sudokuTable_delete(sudoku);
}