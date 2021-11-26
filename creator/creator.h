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

#include "../sudoku/sudokuTable.h"
#include <stdbool.h>

/******************* generateUniqueTable ******************/
/* 
 * generates a sudoku table with a unique solution
 *
 * Caller provides:
 *  the number of spots to be filled with numbers
 * 
 * We return:
 *  a pointer to the new sudoku table; return NULL on error
 * 
 * generates a completely solved sudoku until it is unique, then returns
 */
sudokuTable_t* createUniqueTable(int numFilled, int dimension);


/******************* generate ******************/
/* 
 * generates a sudoku table not necessarily with a unique solution
 *
 * Caller provides:
 *  the number of spots to be filled with numbers
 * 
 * We return:
 *  a pointer to the new sudoku table; return NULL on error
 * 
 * generates a completely solved sudoku table via brute force. This mean that 
 * all valid sudoku boards will have equal probability of being generated. 
 */
sudokuTable_t* generate(int numFilled, int dimension);


/******************* checkUniqueness ******************/
/*
 * checks whether a sudoku board has a unique or multiple solutions. 
 *
 * Caller provides:
 *  valid sudoku board 
 *  
 * 
 * We return:
 *  true if the sudoku board has one solution
 *  false if it has multiple
 * 
 * We guarantee:
 *  nothing if the sudoku board is not valid
 * 
 * Caller is responsible for later freeing the memory allocated,
 * typically by calling sudokuTable_delete
 */
bool checkUniqueness(sudokuTable_t* sudoku, int dimension);


/******************* randomize ******************/
/*
 * takes in array and randomizes the order of the array 
 *
 * Caller provides:
 *  array of ints and dimension or size of the array
 *  
 * 
 * We return:
 *  nothing
 * 
 * We guarantee:
 *  the array will be shuffled 
 */
void randomize(int* arr, int dimension);


/******************* backtrackRand ******************/
/*
 * attempts solve a sudoku board passed to it in place (does not use extra memory). However, this differs
 * from our backtrack algorithm in solver.c because it tries the candidates in a cell in random order. 
 *
 * Caller provides:
 *  nothing, this will be implicity called in solveSudoku
 *  
 * We return:
 *  boolean return type which does hold any significance, just for backtracking recursion. 
 * 
 * We guarantee:
 *  sudoku board will be solved if valid
 * 
 * Caller is responsible for later freeing the memory allocated,
 * typically by calling sudokuTable_delete
 */
bool backtrackRand(int** board, int r, int c,  bool** row, bool** col, bool*** boxes, int dimension, int* arr);

#endif
