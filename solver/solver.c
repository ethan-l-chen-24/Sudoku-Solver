/*
 * solver.c : solves an inputted sudoku board
 *
 * usage: ./sudoku solve difficulty
 * 
 * Bansharee Ireen, Ethan Chen, Jeffrey Jiang
 * Nov 4, 2021
 * 
 * CS50, Fall 2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include "solver.h"
#include "validator.h"
#include "../sudoku/sudokuTable.h"

pthread_mutex_t mutexSolve = PTHREAD_MUTEX_INITIALIZER; // mutex used for server-client multi-thread synchro

/********************* backtrack ***********************/
/* see solver.h for more information 
 *
 * for direction: 1 means increasing order (use by default), -1 means decreasing order
*/
bool solveSudoku(sudokuTable_t * sudoku, int direction, int dimension) {

    pthread_mutex_lock( & mutexSolve); // mutex lock for thread synchronization
    int sqrtDimension = sqrt(dimension);

    if (sudoku == NULL) {
        pthread_mutex_unlock(&mutexSolve);
        return false;
    }

    int ** board = sudokuTable_board(sudoku);

    //these will hold which numbers are in each row, col, and box. So if the number 5 is at coordinates (i, j), then row[i][5] = true denoting there is a 5 in row i. 
    //likewise, col[j][5] = true, and boxes[i/3][j/3][5] = true.

    validator_t* val = validator_new(dimension);
    bool** row = validator_getRow(val);
    bool** col = validator_getCol(val);
    bool*** boxes = validator_getBoxes(val);

    int num = 0;
    bool invalid = false;

    //now we start setting numbers to true given what's already on the board. This will also check for invalid entries while it's filling in. 
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (board[i][j] == 0) continue;
            num = board[i][j];

            // if the row has the num
            if (row[i][num]) {
                invalid = true;
                fprintf(stderr, "%d already exists in row\n", num);
            } else row[i][num] = true;

            // if the column has the num
            if (col[j][num]) {
                invalid = true;
                fprintf(stderr, "%d already exists in col\n", num);
            } else col[j][num] = true;

            // if the boxes have the num
            if (boxes[i / sqrtDimension][j / sqrtDimension][num]) {
                invalid = true;
                fprintf(stderr, "%d already exists in box\n", num);
            } else boxes[i / sqrtDimension][j / sqrtDimension][num] = true;
        }
    }

    // if the current state of the board is valid
    if (!invalid) {

        // solve the board forwards or backwards
        if (direction == 1) {
            backtrack(board, 0, 0, row, col, boxes, dimension);
        } else backtrackRev(board, 0, 0, row, col, boxes, dimension);

        validator_delete(val);

        // if it is solved (cells are filled in) return true;
        if (!isSolved(sudoku, dimension)) {
            pthread_mutex_unlock(&mutexSolve);
            return false;
        }

        pthread_mutex_unlock(&mutexSolve);
        return true;

    } 
    else {
        validator_delete(val);
        fprintf(stderr, "Invalid board\n");
        pthread_mutex_unlock(&mutexSolve);
        return false;
    }
} //end solve

/********************* backtrack ***********************/
/* backtracking algo: it will recur along columns first, and then move along the rows.
 *
 * see solver.h for more information 
*/
bool backtrack(int ** board, int r, int c, bool ** row, bool ** col, bool ** * boxes, int dimension) {
    //if we succesfully filled a whole column
    if (c == dimension) {
        c = 0;
        //move onto the next row
        r++;

        //we have all cols from the top left so we are done
        if (r == dimension) {
            return true;
        } 

    } 

    //if there is an empty space
    if (board[r][c] == 0) {

        //we try all numbers
        for (int num = 1; num <= dimension; num++) {

            //only if it adheres to sudoku rules
            if (!(row[r][num] || col[c][num] || boxes[r / (int)(sqrt(dimension))][c / (int)(sqrt(dimension))][num])) {
                //now if we come across a valid candidate, insert it into the board and try to progress
                row[r][num] = true;
                col[c][num] = true;
                boxes[r / (int)(sqrt(dimension))][c / (int)(sqrt(dimension))][num] = true;
                board[r][c] = num;

                //so we recur onto next slot and see if our candidate from above is valid
                if (backtrack(board, r, c + 1, row, col, boxes, dimension)) return true;

                //we reset our board so we don't disrupte backtracking from other slots
                board[r][c] = 0;
                row[r][num] = false;
                col[c][num] = false;
                boxes[r / (int)(sqrt(dimension))][c / (int)(sqrt(dimension))][num] = false;
            }
        }
    } 

    //already a number so move on
    else return backtrack(board, r, c + 1, row, col, boxes, dimension);

    return false;
} 

/********************* backtrackRev ***********************/
/* backtracking algo: it will recur along columns first, and then move along the rows.
 * this is the reverse direction of backtrack
 *
 * see solver.h for more information 
*/
bool backtrackRev(int ** board, int r, int c, bool ** row, bool ** col, bool ** * boxes, int dimension) {
    //if we succesfully filled a whole column
    if (c == dimension) {
        c = 0;
        //move onto the next row
        r++;
        if (r == dimension)
            return true;
    }

    //we have all cols from the top left so we are done
    if (board[r][c] == 0) {
        for (int num = dimension; num >= 1; num--) {
            if (!(row[r][num] || col[c][num] || boxes[r / (int)(sqrt(dimension))][c / (int)(sqrt(dimension))][num])) {
                //now if we come across a valid candidate, insert it into the board and try to progress
                row[r][num] = true;
                col[c][num] = true;
                boxes[r / (int)(sqrt(dimension))][c / (int)(sqrt(dimension))][num] = true;
                board[r][c] = num;

                //so we recur onto next slot and see if our candidate from above is valid
                if (backtrackRev(board, r, c + 1, row, col, boxes, dimension)) return true;

                //we reset our board so we don't disrupte backtracking from other slots
                board[r][c] = 0;
                row[r][num] = false;
                col[c][num] = false;
                boxes[r / (int)(sqrt(dimension))][c / (int)(sqrt(dimension))][num] = false;
            }
        }
    } 

    // already a number so move on
    else return backtrackRev(board, r, c + 1, row, col, boxes, dimension);

    return false;
} 

/********************* isSolved ***********************/
/* see solver.h for more information */
bool isSolved(sudokuTable_t * sudoku, int dimension) {
    int ** board = sudokuTable_board(sudoku);

    // if any of the cells are 0, it was not solvable
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            if (board[row][col] == 0) {
                return false;
            }
        }
    }
    return true;
}