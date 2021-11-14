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
#include "file.h"

// local functions
static bool validVal(sudokuTable_t * sudoku, int val);
static bool validInd(sudokuTable_t * sudoku, int ind);
static void printRowBar(FILE * fp, int sqrtDimension);
static void sudokuTable_setFormat(sudokuTable_t * sudoku, bool format);

// global types
typedef struct sudokuTable {
    int ** table; // the sudoku table
    int dimension; // the dimension of the table
    bool format; // the print format of the table; true = stylized, false = standard
}
sudokuTable_t;

/******************* sudokuTable_new ******************/
/* see sudokuTable.h for more information */
sudokuTable_t * sudokuTable_new(int dimension, bool format) {
    if (dimension <= 0) return NULL;

    sudokuTable_t * sudoku = malloc(sizeof(sudokuTable_t));

    if (sudoku == NULL) {
        return NULL;
    } else {
        // allocate memory for the table
        int ** matrix = calloc(dimension, sizeof(int * ));
        if (matrix == NULL) {
            free(sudoku);
            return NULL;
        }

        // alocating memory for each cell
        for (int i = 0; i < dimension; i++) {
            int * row = calloc(dimension, sizeof(int));
            matrix[i] = row;
        }

        // assign data members
        sudoku -> table = matrix;
        sudoku -> dimension = dimension;
        sudoku -> format = format;

        return sudoku;
    }
}

/******************* sudokuTable_board ******************/
/* see sudokuTable.h for more information */
int ** sudokuTable_board(sudokuTable_t * sudoku) {
    if (sudoku == NULL) return NULL;
    else return sudoku -> table;
}

/******************* sudokuTable_dimension ******************/
/* see sudokuTable.h for more information */
int sudokuTable_dimension(sudokuTable_t * sudoku) {
    if (sudoku == NULL) return 0;
    else return sudoku -> dimension;
}

/******************* sudokuTable_load ******************/
/* see sudokuTable.h for more information */
sudokuTable_t * sudokuTable_load(FILE * fp, int dimension) {
    if (fp == NULL) return NULL;

    char currCharr;         // the current character read from the file
    char prevChar = '\0';   // tracks the previous character
    char number[4];         // numerical string to insert into the board
    int insert;             // the integer to insert into the board

    int row = 0;
    int col = 0;

    int numReceived = 0;    // tracks the number of non-zero numbers
    bool format = false;

    sudokuTable_t * sudoku = sudokuTable_new(dimension, false);
    while (!feof(fp)) {
        while ((currCharr = fgetc(fp)) != '\n' && currCharr != EOF) {
            // if there is a space after the last digit
            // then this is the end of the number
            if (isspace(currCharr) && isdigit(prevChar)) {
                sudokuTable_set(sudoku, row, col, insert);  // add the number to the table
                col++;                                      // move to the next column        
            }

            // if current char is a digit
            else if (isdigit(currCharr)) {
                insert = (int) currCharr - '0'; // convert to integer

                // if previous char was also a digit, this is a 2-digit number on a 16x16 board
                if (isdigit(prevChar)) {
                    sprintf(number, "%c%c", prevChar, currCharr);   // concatenate the two digits
                    insert = atoi(number);                          // set the two digit number to be the integer to insert
                }

                if (col >= dimension || row >= dimension) {
                    sudokuTable_delete(sudoku);
                    fprintf(stderr, "Error: format of input file is incorrect\n");
                    return NULL;
                }

                // increment if non-zero
                if (insert != 0) numReceived++;
            }

            // if there is an alphabet in the board
            else if (isalpha(currCharr)) {
                sudokuTable_delete(sudoku);
                fprintf(stderr, "Error: format of input file is incorrect\n");
                return NULL;
            } else {
                format = true;
            }

            // update the previous character
            prevChar = currCharr;
        }

        // if following standard format and there is no space after the number
        // then the number was not added above, so add it here
        if (!format && !isspace(prevChar)) {
            sudokuTable_set(sudoku, row, col, insert);
            col++;
        }

        // it should have passed all columns in the row
        // if not, format is incorrect
        if (col != dimension && col != 0) {
            sudokuTable_delete(sudoku);
            fprintf(stderr, "Error: format of input file is incorrect\n");
            return NULL;
        }

        // go to the next row if not at beginning of row
        if (col != 0) {
            row++;
        }

        col = 0;            // resetting column number at new row
        prevChar = '\0';    // resetting prevChar to null character for new row
    }

    // if we did not go through the required number of rows
    if (row != dimension) {
        sudokuTable_delete(sudoku);
        fprintf(stderr, "Error: format of input file is incorrect\n");
        return NULL;
    }

    // check if received at least 25 numbers for dimension 9
    if (dimension == 9 && numReceived < 25) {
        fprintf(stderr, "Invalid board. Needs to have at least 25 starting numbers.\n");
        return NULL;
    } // check if received at least 135 numbers for dimension 16 
    else if (dimension == 25 && numReceived < 135) {
        fprintf(stderr, "Invalid board. Needs to have at least 135 starting numbers.\n");
        return NULL;
    } // check if received at least 5 numbers for dimension 4 
    else if (numReceived < 4) {
        fprintf(stderr, "Invalid board. Needs to have at least 5 starting numbers.\n");
        return NULL;
    }
    sudokuTable_setFormat(sudoku, format);
    return sudoku;
}

/******************* sudokuTable_set ******************/
/* see sudokuTable.h for more information */
void sudokuTable_set(sudokuTable_t * sudoku, int row, int col, int val) {
    if (sudoku != NULL && validInd(sudoku, row) && validInd(sudoku, col) && validVal(sudoku, val)) {
        int ** table = sudoku -> table;
        table[row][col] = val;
    }
}

/******************* sudokuTable_get ******************/
/* see sudokuTable.h for more information */
int sudokuTable_get(sudokuTable_t * sudoku, int row, int col) {
    if (sudoku != NULL && validInd(sudoku, row) && validInd(sudoku, col)) {
        int ** table = sudoku -> table;
        return table[row][col];
    } else {
        return 0;
    }
}

/******************* sudokuTable_delete ******************/
/* see sudokuTable.h for more information */
void sudokuTable_delete(sudokuTable_t * sudoku) {
    if (sudoku != NULL) {
        // free each row
        for (int i = 0; i < sudoku -> dimension; i++) {
            free(sudoku -> table[i]);
        }

        // free the table data member first
        free(sudoku -> table);
        // finally, free the struct itself
        free(sudoku);
    }
}

/******************* sudokuTable_print ******************/
/* see sudokuTable.h for more information */
void sudokuTable_print(FILE * fp, sudokuTable_t * sudoku) {
    if (sudoku == NULL) return;

    // get the table and dimension from the struct
    int ** table = sudoku -> table;
    int dimension = sudoku -> dimension;
    int sqrtDimension = (int) sqrt(dimension);

    if (table == NULL) return;

    // simple style, just the numbers
    if (!sudoku -> format) {

        // loop through every cell
        for (int row = 0; row < dimension; row++) {
            for (int col = 0; col < dimension; col++) {
                fprintf(fp, "%d ", table[row][col]); // print the number
            }

            // print to next line
            fprintf(fp, "\n");
        }
    } else {

        // complex style, includes | and _ to explicitly show 3x3 boxes
        int rowCount = 0;
        int columnCount = 0;

        printRowBar(fp, sqrtDimension);
        fprintf(fp, "| ");

        // loop through every cell
        for (int row = 0; row < dimension; row++) {
            for (int col = 0; col < dimension; col++) {
                fprintf(fp, "%2d ", table[row][col]); // print the number

                // every three columns print a vertical bar
                columnCount++;
                if (columnCount % sqrtDimension == 0) {
                    fprintf(fp, "| ");
                }
            }

            // every three rows print a full row of underscores
            rowCount++;
            if (rowCount % sqrtDimension == 0) {
                fprintf(fp, "\n");
                printRowBar(fp, sqrtDimension);

                if (rowCount != dimension) {
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
static bool validVal(sudokuTable_t * sudoku, int val) {
    if (sudoku == NULL) return false;
    return (val >= 0 && val <= sudoku -> dimension);
}

// checks if the value for row or column is within the acceptable range
static bool validInd(sudokuTable_t * sudoku, int ind) {
    if (sudoku == NULL) return false;
    return (ind >= 0 && ind < sudoku -> dimension);
}

/******************* printRowBar ******************/
/* print a long row bar _______________________ */
static void printRowBar(FILE * fp, int sqrtDimension) {
    fprintf(fp, "-");
    for (int i = 0; i < sqrtDimension; i++) {
        for (int j = 0; j < sqrtDimension; j++) {
            fprintf(fp, "---");
        }
        fprintf(fp, "--");
    }
    fprintf(fp, "\n");
}

/******************* sudokuTable_setFormat ******************/
/* changes the format param of a sudokuTable struct to the designated style */
static void sudokuTable_setFormat(sudokuTable_t * sudoku, bool format) {
    if (sudoku == NULL) return;
    sudoku -> format = format;
}