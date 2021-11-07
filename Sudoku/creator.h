/*
 * creator.h - header file for creater.c
 * 
 * Bansharee Ireen, Ethan Chen, Jeffrey Jiang
 * Nov 4, 2021
 * 
 * CS50, Fall 2021
 */

#ifndef __CREATOR
#define __CREATOR

#include "sudokuTable.h"

/******************* generateTable ******************/
/* 
 * generates a sudoku table with a unique solution
 *
 * Caller provides:
 *  the number of spots to be filled with numbers
 * 
 * We return:
 *  a pointer to the new sudoku table; return NULL on error
 */
sudokuTable_t* generateTable(int numFilled);

#endif
