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
#include <ctype.h>
#include "sudokuTable.h"
#include "../libcs50/file.h"

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

        // alocating memory for each cell
        for(int i = 0; i < dimension; i++) {
            int* row = calloc(dimension, sizeof(int));
            matrix[i] = row;
        }

        // assign data members
        sudoku->table = matrix;
        sudoku->dimension = dimension;

        return sudoku;
    }
}

/******************* sudokuTable_board ******************/
/* see sudokuTable.h for more information */
int** sudokuTable_board(sudokuTable_t* sudoku) {
    if(sudoku == NULL) return NULL;
    else return sudoku->table;
}

/******************* sudokuTable_load ******************/
/* see sudokuTable.h for more information */
sudokuTable_t* sudokuTable_load(FILE* fp, int dimension) {
    if(fp == NULL) return NULL;

    sudokuTable_t* sudoku = sudokuTable_new(9);
    char c;
    int row = 0;
    int col = 0;
    bool rowBar = false;

    while(!feof(fp)) {
        while((c = fgetc(fp)) != '\n' && c != EOF) {
            // if the line has one '-', the line should only contain the characters '-'
            if (!rowBar && c == '-') {
                rowBar = true;  // set to true as line is rowBar
                break;          // break to leave row
            } 
            else {
                rowBar = false;
            }

            printf("character: %c\n", c);
            if(isdigit(c)) {
                printf("digit: %c\n", c);

                if(col >= 9 || row >= 9) {
                    printf("col: %d, row: %d\n", col, row);
                    sudokuTable_delete(sudoku);
                    fprintf(stderr, "Error 1: format of input file is incorrect\n");
                    return NULL;
                }
                sudokuTable_set(sudoku, row, col, (int) c - '0');

                col++;
            }
        }
        // if the line was not a bar, it should have passed 9 columns
        // if not, format is incorrect
        if(col != 9 && !rowBar) {
            sudokuTable_delete(sudoku);
            fprintf(stderr, "Error 2: format of input file is incorrect\n");
            return NULL;
        }

        if (!rowBar) {
            row++;
        }
        col = 0;
    }
    
    return sudoku;
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
/* see sudokuTable.h for more information */
int sudokuTable_get(sudokuTable_t* sudoku, int row, int col) {
    if (sudoku != NULL && validInd(sudoku, row) && validInd(sudoku, col)) {
        int** table = sudoku->table;
        return table[row][col];
    } else {
        return 0;
    }
}

/******************* sudokuTable_delete ******************/
/* see sudokuTable.h for more information */
void sudokuTable_delete(sudokuTable_t* sudoku) {
    if (sudoku != NULL) {
        // free each row
        for(int i = 0; i < 9; i++) {
            free(sudoku->table[i]);
        }

        // free the table data member first
        free(sudoku->table);
        // finally, free the struct itself
        free(sudoku);
    }
}

/******************* printTable() ******************/
/* see sudokuTable.h for more information */
void sudokuTable_print(sudokuTable_t* sudoku, bool style) {
    if(sudoku == NULL) return;

    // get the table and dimension from the struct
    int** table = sudoku->table;
    int dimension = sudoku->dimension;

    if(table == NULL) return;

    // simple style, just the numbers
    if(!style) {

        // loop through every cell
        for(int row = 0; row < dimension; row++) {
            for(int col = 0; col < dimension; col++) {
                printf("%d ", table[row][col]); // print the number
            }

            // print to next line
            printf("\n");
        }
    } else {

    // complex style, includes | and _ to explicitly show 3x3 boxes
        int rowCount = 0;
        int columnCount = 0;

        printRowBar();
        printf("| ");

        // loop through every cell
        for(int row = 0; row < dimension; row++) {
            for(int col = 0; col < dimension; col++) {
                printf("%d ", table[row][col]); // print the number

                // every three columns print a vertical bar
                columnCount++;
                if (columnCount % 3 == 0) {
                    printf("| ");
                }
            }

            // every three rows print a full row of underscores
            rowCount++;
            if(rowCount % 3 == 0) {
                printRowBar();

                if(rowCount != 9) {
                    printf("| ");
                }
                
            } else {
                printf("\n| ");
            }
        }
    }
}

// local functions for defensive programming
// checks if the value to be inserted into the table can be inserted
static bool validVal(sudokuTable_t* sudoku, int val) {
    return (val >= 0 && val <= sudoku->dimension);
}

// checks if the value for row or column is within the acceptable range
static bool validInd(sudokuTable_t* sudoku, int ind) {
    return (ind >= 0 && ind < sudoku->dimension);
}

/******************* swapRow() ******************/
/* print a long row bar _______________________ */
static void printRowBar(void) {
    printf("\n-------------------------\n");
}