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
#include <math.h>
#include "sudokuTable.h"
#include "../libcs50/file.h"

// local functions
static bool validVal(sudokuTable_t* sudoku, int val);
static bool validInd(sudokuTable_t* sudoku, int ind);
static void printRowBar(FILE* fp);
static void sudokuTable_setFormat(sudokuTable_t* sudoku, bool format);

// global types
typedef struct sudokuTable {
    int** table;        // the sudoku table
    int dimension;      // the dimension of the table
    bool format;        // the print format of the table; true = stylized, false = standard
} sudokuTable_t;

/******************* sudokuTable_new ******************/
/* see sudokuTable.h for more information */
sudokuTable_t* sudokuTable_new(int dimension, bool style) {
    if(dimension <= 0) return NULL;

    sudokuTable_t* sudoku = malloc(sizeof(sudokuTable_t));

    if (sudoku == NULL) {
        return NULL;
    } 
    else {
        // allocate memory for the table
        int** matrix = calloc(dimension, sizeof(int*));
        if(matrix == NULL) {
            free(sudoku);
            return NULL;
        }

        // alocating memory for each cell
        for(int i = 0; i < dimension; i++) {
            int* row = calloc(dimension, sizeof(int));
            matrix[i] = row;
        }

        // assign data members
        sudoku->table = matrix;
        sudoku->dimension = dimension;
        sudoku->style = style;

        return sudoku;
    }
}

/******************* sudokuTable_board ******************/
/* see sudokuTable.h for more information */
int** sudokuTable_board(sudokuTable_t* sudoku) {
    if(sudoku == NULL) return NULL;
    else return sudoku->table;
}

/******************* sudokuTable_dimension ******************/
/* see sudokuTable.h for more information */
int sudokuTable_dimension(sudokuTable_t* sudoku) {
    if(sudoku == NULL) return 0;
    else return sudoku->dimension;
}

/******************* sudokuTable_load ******************/
/* see sudokuTable.h for more information */
sudokuTable_t* sudokuTable_load(FILE* fp, int dimension) {
    if(fp == NULL) return NULL;

    char c;
    int row = 0;
    int col = 0;
    bool format = false;

    sudokuTable_t* sudoku = sudokuTable_new(9, false);
    while(!feof(fp)) {
        while((c = fgetc(fp)) != '\n' && c != EOF) {
            if(isdigit(c)) {
                if(col >= dimension || row >= dimension) {
                    sudokuTable_delete(sudoku);
                    fprintf(stderr, "Error: format of input file is incorrect\n");
                    return NULL;
                }
                sudokuTable_set(sudoku, row, col, (int) c - '0');

                col++;
            } else if(isalpha(c)) {
                sudokuTable_delete(sudoku);
                fprintf(stderr, "Error: format of input file is incorrect\n");
                return NULL;
            } else {
                format = true;
            }
        }
        // if the line was not a bar, it should have passed 9 columns
        // if not, format is incorrect
        if(col != dimension && col != 0) {
            sudokuTable_delete(sudoku);
            fprintf(stderr, "Error: format of input file is incorrect\n");
            return NULL;
        }

        if (col != 0) {
            row++;
        }
        col = 0;
    }

    if(row != dimension) {
        sudokuTable_delete(sudoku);
        fprintf(stderr, "Error: format of input file is incorrect\n");
        return NULL;
    }
    
    sudokuTable_setFormat(sudoku, format);
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
        for(int i = 0; i < sudoku->dimension; i++) {
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
void sudokuTable_print(FILE* fp, sudokuTable_t* sudoku) {
    if(sudoku == NULL) return;

    // get the table and dimension from the struct
    int** table = sudoku->table;
    int dimension = sudoku->dimension;
    int sqrtDimension = (int) sqrt(dimension);

    if(table == NULL) return;

    // simple style, just the numbers
    if(!sudoku->format) {

        // loop through every cell
        for(int row = 0; row < dimension; row++) {
            for(int col = 0; col < dimension; col++) {
                fprintf(fp, "%d ", table[row][col]); // print the number
            }

            // print to next line
            fprintf(fp, "\n");
        }
    } else {

    // complex style, includes | and _ to explicitly show 3x3 boxes
        int rowCount = 0;
        int columnCount = 0;

        printRowBar(fp);
        fprintf(fp, "| ");

        // loop through every cell
        for(int row = 0; row < dimension; row++) {
            for(int col = 0; col < dimension; col++) {
                fprintf(fp, "%d ", table[row][col]); // print the number

                // every three columns print a vertical bar
                columnCount++;
                if (columnCount % sqrtDimension == 0) {
                    fprintf(fp, "| ");
                }
            }

            // every three rows print a full row of underscores
            rowCount++;
            if(rowCount % sqrtDimension == 0) {
                fprintf(fp, "\n");
                printRowBar(fp);

                if(rowCount != dimension) {
                    fprintf(fp, "| ");
                }
                
            } else {
                fprintf(fp, "\n| ");
            }
        }
    }
}

// local functions for defensive programming
// checks if the value to be inserted into the table can be inserted
static bool validVal(sudokuTable_t* sudoku, int val) {
    if(sudoku == NULL) return false;
    return (val >= 0 && val <= sudoku->dimension);
}

// checks if the value for row or column is within the acceptable range
static bool validInd(sudokuTable_t* sudoku, int ind) {
    if(sudoku == NULL) return false;
    return (ind >= 0 && ind < sudoku->dimension);
}

/******************* swapRow() ******************/
/* print a long row bar _______________________ */
static void printRowBar(FILE* fp) {
    fprintf(fp, "-------------------------\n");
}

/******************* swapRow() ******************/
/* changes the format param of a sudokuTable struct to the designated style */
static void sudokuTable_setFormat(sudokuTable_t* sudoku, bool format) {
    if(sudoku == NULL) return;
    sudoku->format = format;
}