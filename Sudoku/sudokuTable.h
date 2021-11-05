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
void sudokuTable_get(sudokuTable_t* sudoku, int row, int col);

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