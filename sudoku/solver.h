/*
 *
 *
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "sudokuTable.h"

/******************* solveSudoku ******************/
/*
 * attempts to solve a sudoku puzzle, will print out invalid message if invalid board.
 *
 * Caller provides:
 *  valid sudoku board struct
 *  pass the integer 1 as paramter to direction 
 * 
 * We return:
 *  nothing
 * 
 * We guarantee:
 *  sudoku board will be solved if valid, otherwise will receive error message
 * 
 * Caller is responsible for later freeing the memory allocated,
 * typically by calling sudokuTable_delete
 */
bool solveSudoku(sudokuTable_t* sudoku, int direction);

/******************* backtrack ******************/
/*
 * attempts solve a sudoku board passed to it in place (does not use extra memory). 
 *
 * Caller provides:
 *  nothing, this will be implicity called in solveSudoku
 *  
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
bool backtrack(int** board, int r, int c,  bool row[9][10], bool col[9][10], bool boxes[3][3][10]);


/******************* backtrackRev ******************/
/*
 * Same exact method as above but it checks the candidates in descending order rather than increasing as above. 
 *
 * Caller provides:
 *  nothing, this will be implicity called in solveSudoku
 *  
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
bool backtrackRev(int** board, int r, int c,  bool row[9][10], bool col[9][10], bool boxes[3][3][10]);

/******************* isSolved ******************/
/*
 * checks if a sudoku board is completely solved
 *
 * Caller provides:
 *  a valid pointer to a sudoku table
 * 
 * We return:
 *  boolean return type true if board is solved (no zeroes), false otherwise
 */
bool isSolved(sudokuTable_t* sudoku);
