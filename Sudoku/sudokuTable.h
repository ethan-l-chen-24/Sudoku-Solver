/*
 * sudokuTable.h - header file for the sudoku table struct
 *
 * A sudoku table holds an int** table of a certain dimension, typically 9x9
 * 
 * Ethan Chen, Jeffrey Jiang, Bansharee Ireen
 * 
 * Nov 4 2021
 * CS50 Fall, 2021
 */

#include <stdbool.h>

typedef struct sudokuTable sudokuTable_t;

/******************* sudokuTable_new ******************/
/*
 * Create a new, empty sudoku table.
 *
 * Caller provides:
 *  valid integer to be used as the table's dimensions
 * 
 * We return:
 *  a pointer to the new sudoku table; return NULL on error
 * 
 * We guarantee:
 *  sudokuTable is initialized empty after memory allocation
 * 
 * Caller is responsible for later freeing the memory allocated,
 * typically by calling sudokuTable_delete
 */
sudokuTable_t* sudokuTable_new(int dimension);

/******************* sudokuTable_set ******************/
/*
 * Sets the value of an individual cell to value provided
 *
 * Caller provides:
 *  valid integers for the row, column, and value; valid pointer to a
 *  sudokuTable
 * 
 * Internally checks if the integer values provided are valid, 
 * according to the rules of sudoku
 * 
 */
void sudokuTable_set(sudokuTable_t* sudoku, int row, int col, int val);


/******************* sudokuTable_set ******************/
/*
 * Returns the value of an individual cell
 *
 * Caller provides:
 *  valid integers for the row and column, valid pointer to a
 *  sudokuTable
 * 
 * Internally checks if the integer values provided are valid, 
 * according to the rules of sudoku
 * 
 */
int sudokuTable_get(sudokuTable_t* sudoku, int row, int col);

/******************* sudokuTable_set ******************/
/*
 * Deletes a previously created sudoku table
 *
 * Caller provides:
 *  valid pointer to a sudokuTable
 * 
 * Frees memory created by sudokuTable_new
 * 
 */
void sudokuTable_delete(sudokuTable_t* sudoku);

/******************* printTable() ******************/
/*
 * Prints a hashtable to stdout
 * if in style mode, it stylizes the grid with | and _ to show the 3x3 boxes
 * 
 * Caller provides:
 *  valid pointer to a sudokuTable, boolean for advanced or simple style
*/
void printTable(sudokuTable_t* sudoku, bool style);

/******************* swapRow() ******************/
/* 
 * swaps two rows in a sudoku table
 *
 * Caller provides:
 *  valid pointer to a sudokuTable, two rows (in no particular order) to swap all values in
*/
void swapRow(sudokuTable_t* sudoku, int row1, int row2);

/******************* swapColumn() ******************/
/* 
 * swaps two columns in a sudoku table
 *
 * Caller provides:
 *  valid pointer to a sudokuTable, two columns (in no particular order) to swap all values in
*/
void swapColumn(sudokuTable_t* sudoku, int col1, int col2);