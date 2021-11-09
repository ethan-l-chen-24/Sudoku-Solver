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

/******************* sudokuTable_board ******************/
/*
 * Return the sudokuBoards board
 *
 * Caller provides:
 *  valid pointer to a sudokuTable
 * 
 * We return:
 *  a pointer to the new sudoku table; return NULL on error
 */
int** sudokuTable_board(sudokuTable_t* sudoku);

/******************* sudokuTable_dimension ******************/
/*
 * Return the sudokuBoards dimension
 *
 * Caller provides:
 *  valid pointer to a sudokuTable
 * 
 * We return:
 *  an int variable with the dimension
 */
int sudokuTable_dimension(sudokuTable_t* sudoku);

/******************* sudokuTable_load ******************/
/*
 * Create a new sudoku table from stdin in one of two formats
 *
 * Caller provides:
 *  valid file that is currently open and being read that contains a sudoku table, 
 *  an int dimension to read the sudoku table into
 * 
 * We return:
 *  a pointer to the new sudoku table; return NULL on error
 * 
 * Caller is responsible for later freeing the memory allocated,
 * typically by calling sudokuTable_delete
 */
sudokuTable_t* sudokuTable_load(FILE* fp, int dimension);

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
void sudokuTable_print(FILE* fp, sudokuTable_t* sudoku, bool style);