/*
 * sudokuTable.h - header file for the sudoku table struct
 *
 * Ethan Chen, Jeffrey Jiang, Bansharee Ireen
 * 
 * Nov 4 2021
 * CS50 Fall, 2021
 */

sudokuTable_t* sudokuTable_new(int dimension);

void sudokuTable_set(sudokuTable_t* sudoku, int row, int col, int val);

void sudokuTable_get(sudokuTable_t* sudoku, int row, int col);

void sudokuTable_delete(sudokuTable_t* sudoku);