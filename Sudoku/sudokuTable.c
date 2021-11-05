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
#include "file.h"

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
sudokuTable_t* sudokuTable_board(sudokuTable_t* sudoku) {
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
    while(!feof(fp)) {
        int col = 0;
        while((c = fgetc(fp)) != '\n') {
            if(isdigit(c)) {

                if(col >= 9 || row >= 9) {
                    sudokuTable_delete(sudoku);
                    fprintf(stderr, "Error: format of input file is incorrect\n");
                    return NULL;
                }
                
                sudokuTable_set(sudoku, row, col, atoi(c));
                col++;
            }
        }

        row++;
        col = 0;
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
void sudokuTable_print(sudokuTable_t* sudoku, bool style)
{
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

/******************* swapRow() ******************/
/* see sudokuLib.h for more information */
void swapRow(sudokuTable_t* sudoku, int row1, int row2)
{

    // loop through every column
    for(int col = 0; col < 9; col++) {
        int val1 = sudokuTable_get(sudoku, row1, col);
        int val2 = sudokuTable_get(sudoku, row2, col);
        sudokuTable_set(sudoku, row2, col, val1);
        sudokuTable_set(sudoku, row1, col, val2);
    }
}

/******************* swapColumn() ******************/
/* see sudokuLib.h for more information */
void swapColumn(sudokuTable_t* sudoku, int col1, int col2) 
{   
    // loop through every row
    for(int row = 0; row < 9; row++) {
        int val1 = sudokuTable_get(sudoku, row, col1);
        int val2 = sudokuTable_get(sudoku, row, col2);
        sudokuTable_set(sudoku, row, col2, val1);
        sudokuTable_set(sudoku, row, col1, val2);
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

/******************* swapRow() ******************/
/* print a long row bar _______________________ */
static void printRowBar(void) {
    printf("\n ----------------------- \n");
}