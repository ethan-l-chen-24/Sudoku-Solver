/* 
 * sudokuLib.h - header file for 'sudokuLib' file in 'Sudoku' module
 *
 * provides a set of functions for a sudoku table, that can print, swap rows, or.....
 * 
 * Ethan Chen, Jeffrey Jiang, Bansharee Ireen, November 2021
 */

#ifndef __SUDOKULIB
#define __SUDOKULIB

#include <stdbool.h>

/******************* functions *******************/

/******************* printTable() ******************/
/*
 * Prints a hashtable to stdout
 * if in style mode, it stylizes the grid with | and _ to show the 3x3 boxes
*/
void printTable(int** table, int dimension, bool style);

/******************* swapRow() ******************/
/*
 * swaps two rows in a sudoku table
*/
void swapRow(int** table, int dimension, int row1, int row2);

/******************* swapColumn() ******************/
/*
 * Swaps two columns in a sudokou table
*/
void swapColumn(int** table, int dimension, int col1, int col2);

#endif