/*
 * solver.h - header file for creater.c
 * 
 * Bansharee Ireen, Ethan Chen, Jeffrey Jiang
 * Nov 4, 2021
 * 
 * CS50, Fall 2021
 */

#ifndef __CREATOR
#define __CREATOR

#include "sudokuTable.h"

/******************* solveSudoku ******************/
/* 
 * solves an inputted sudoku table
 *
 * Caller provides:
 *  a valid pointer to a sudoku table
 */
void solveSudoku(sudokuTable_t* sudoku);

#endif