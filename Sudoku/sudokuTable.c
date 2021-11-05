/*
 * sudokuTable.c - a struct to represent the sudoku board
 *
 * see sudokuTable.h for more information
 *
 * Ethan Chen, Jeffrey Jiang, Bansharee Ireen
 * Nov 4 2021
 * 
 * CS50 Fall, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sudokuTable.h"

// local functions
bool validVal(sudokuTable_t* sudoku, int val);
bool validInd(sudokuTable_t* sudoku, int ind);

// global types
typedef struct sudokuTable {
    int** table;        // the sudoku table
    int dimension;      // the dimension of the table
} sudokuTable_t;

/******************* sudokuTable_new ******************/
/* see sudokuTable.h for more information */
sudokuTable_t* sudokuTable_new(int dimension) {
    sudokuTable_t* sudoku = malloc(sizeof(sudokuTable_t));

    if (sudoku == NULL || dimension < 0) {
        return NULL;
    } 
    else {
        // allocate memory for the table
        int** matrix = calloc(dimension, sizeof(int*));

        // assign data members
        sudoku->table = matrix;
        sudoku->dimension = dimension;

        return sudoku;
    }
}

/******************* sudokuTable_set ******************/
/* see sudokuTable.h for more information */
void sudokuTable_set(sudokuTable_t* sudoku, int row, int col, int val) {
    if (sudoku != NULL && validInd(sudoku, row) && validInd(sudoku, col) && validVal(sudoku, val)) {
        int** table = sudoku->table;
        table[row][col] = val;
    }
}

/******************* sudokuTable_get ******************/
////////////////// idk if we need this but wrote it here cause idk
/* see sudokuTable.h for more information */
void sudokuTable_get(sudokuTable_t* sudoku, int row, int col) {
    if (sudoku != NULL && validInd(sudoku, row) && validInd(sudoku, col)) {
        int** table = sudoku->table;
        return table[row][col];
    }
}

/******************* sudokuTable_delete ******************/
/* see sudokuTable.h for more information */
void sudokuTable_delete(sudokuTable_t* sudoku) {
    if (sudoku != NULL) {
        // free the table data member first
        free(sudoku->table);
        // finally, free the struct itself
        free(sudoku);
    }
}

// local functions for defensive programming
/////////////// idk if we need this level of error checking, but writing them just in case

// checks if the value to be inserted into the table can be inserted
bool validVal(sudokuTable_t* sudoku, int val) {
    return (val >= 0 && val <= sudoku->dimension);
}

// checks if the value for row or column is within the acceptable range
bool validInd(sudokuTable_t* sudoku, int ind) {
    return (ind >= 0 && ind < sudoku->dimension);
}