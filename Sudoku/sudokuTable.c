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
static bool validVal(sudokuTable_t* sudoku, int val);
static bool validInd(sudokuTable_t* sudoku, int ind);
static void printRowBar(void);

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
static bool validVal(sudokuTable_t* sudoku, int val) {
    return (val >= 0 && val <= sudoku->dimension);
}

// checks if the value for row or column is within the acceptable range
static bool validInd(sudokuTable_t* sudoku, int ind) {
    return (ind >= 0 && ind < sudoku->dimension);
}

/******************* printTable() ******************/
/* see sudokuLib.h for more information */
void printTable(sudokuTable_t* sudoku, bool style)
{
    // get the table and dimension from the struct
    int** table = sudoku->table;
    int dimension = sudoku->dimension;

    if(table == NULL) return;

    // simple style, just the numbers
    if(!style) {

        // loop through every cell
        for(int i = 0; i < dimension; i ++) {
            for(int j = 0; j < dimension; j++) {
                printf("%d ", table[i][j]); // print the number
            }

            // print to next line
            printf("\n");
        }
    } else {

    // complex style, includes | and _ to explicitly show 3x3 boxes
        int rowCount = 0;
        int columnCount = 0;

        printRowBar();
        printf("|");

        // loop through every cell
        for(int i = 0; i < dimension; i ++) {
            for(int j = 0; j < dimension; j++) {
                printf("%d ", table[i][j]); // print the number

                // every three columns print a vertical bar
                columnCount++;
                if (columnCount % 3 == 0) {
                    printf("|");
                }
            }

            // every three rows print a full row of underscores
            rowCount++;
            if(rowCount % 3 == 0) {
                printRowBar();
            }

            // print next line
            printf("\n|");
        }
    }
}

/******************* swapRow() ******************/
/* print a long row bar _______________________ */
static void printRowBar(void) {
    printf("___________\n");
}

/******************* swapRow() ******************/
/* see sudokuLib.h for more information */
void swapRow(sudokuTable_t* sudoku, int row1, int row2)
{
    // get the table and dimension from the struct
    int** table = sudoku->table;
    int dimension = sudoku->dimension;

    // loop through every column
    int save;
    for(int col = 0; col < dimension; col++) {
        save = table[row1][col]; // save the row cell
        table[row1][col] = table[row2][col]; // swap the two values in each row
        table[row2][col] = save;
    }
}

/******************* swapColumn() ******************/
/* see sudokuLib.h for more information */
void swapColumn(sudokuTable_t* sudoku, int col1, int col2) 
{
    // get the table and dimension from the struct
    int** table = sudoku->table;
    int dimension = sudoku->dimension;
    
    // loop through every row
    int save;
    for(int row = 0; row < dimension; row++) {
        save = table[row][col1]; // save the column cell
        table[row][col1] = table[row][col2]; // swap the two values in each column
        table[row][col2] = save;
    }
}