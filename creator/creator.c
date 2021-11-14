/*
 * creator.c - creates the sudoku board
 *
 * usage: ./sudoku create difficulty
 * 
 * Bansharee Ireen, Ethan Chen, Jeffrey Jiang
 * Nov 4, 2021
 * 
 * CS50, Fall 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include "creator.h"
#include "validator.h"
#include "solver.h"
#include "../sudoku/sudokuTable.h"

pthread_mutex_t mutexGenerate = PTHREAD_MUTEX_INITIALIZER; // mutex used for server-client multi-thread synchro

/******************* generateUniqueTable() ******************/
/* see creator.h for more information */
sudokuTable_t* createUniqueTable(int numFilled, int dimension) {
    pthread_mutex_lock( & mutexGenerate); // synchronization

    sudokuTable_t* sudokuTable = generate(numFilled, dimension); // generate a new table
    int** table = sudokuTable_board(sudokuTable); // retrieve the board from the table

    // initialize variables
    int check = 0;
    bool uniq = false;
    int x = 0;
    int y = 0;
    int tmp = 0;
    int plucks = 0;
    while (!uniq) {

        // choose a random row and column
        x = rand() % dimension;
        y = rand() % dimension;

        if (table[x][y] != 0) {
            plucks++;
            tmp = table[x][y];
            table[x][y] = 0;
            // if the table is unique, move onto the next pluck
            if (checkUniqueness(sudokuTable, dimension)) {
                check++;
            } else { // otherwise try another number
                table[x][y] = tmp;
            }

        } 

        // check if can't find any cells to pluck that will keep the board unique (aka if checking for too long)
        if (plucks >= 2 * (dimension * dimension)) {

            // delete the board and start over
            sudokuTable_delete(sudokuTable);
            sudokuTable = generate(numFilled, dimension);
            table = sudokuTable_board(sudokuTable);
            plucks = 0;
            check = 0;
        } 

        // if only numFilled numbers left on the board and stil unique, we are done
        if (check == (dimension * dimension) - numFilled) {
            uniq = true;
        } 

    } 

    pthread_mutex_unlock(&mutexGenerate); // unlock the mutex so other threads can run
    return sudokuTable;
} //end generateTable

/******************* generate() ******************/
/* see creator.h for more information */
sudokuTable_t* generate(int numFilled, int dimension) {
    // create a new table
    sudokuTable_t* sudoku = sudokuTable_new(dimension, true);

    if (sudoku == NULL) {
        return NULL;
    }

    // retrieve the arrays from 
    int** board = sudokuTable_board(sudoku);
    validator_t* val = validator_new(dimension);
    bool** row = validator_getRow(val);
    bool** col = validator_getCol(val);
    bool*** boxes = validator_getBoxes(val);

    // create an array from 1-9 to represent each number
    int arr[dimension];
    for (int i = 1; i <= dimension; i++) {
        arr[i - 1] = i;
    }

    // generate a random completely filled board
    randomize(arr, dimension);
    backtrackRand(board, 0, 0, row, col, boxes, dimension, arr); // backtrack and pluck out of that board
    validator_delete(val);

    return sudoku;
}


/******************* checkUniqueness() ******************/
/* 
 * see creator.h for more information 
 *
 * returns true if sudoku board is unique
 * returns false if there are multiple solutions detected
*/
bool checkUniqueness(sudokuTable_t* sudoku, int dimension) {

    // validate sudoku arg
    if (sudoku == NULL) {
        return false;
    } 

    int** table1 = sudokuTable_board(sudoku);

    // create two copies of the original board
    sudokuTable_t * s2 = sudokuTable_new(dimension, true);
    sudokuTable_t * s3 = sudokuTable_new(dimension, true);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            sudokuTable_set(s2, i, j, table1[i][j]);
            sudokuTable_set(s3, i, j, table1[i][j]);
        } 
    } 

    // grab the tables from those boards
    int** table2 = sudokuTable_board(s2);
    int** table3 = sudokuTable_board(s3);

    //get two sudoku boards, solve one with foward and the other with rev backtrack
    if (!solveSudoku(s3, 1, dimension)) {
        sudokuTable_delete(s2);
        sudokuTable_delete(s3);
        return false;
    }

    if (!solveSudoku(s2, 0, dimension)) {
        sudokuTable_delete(s2);
        sudokuTable_delete(s3);
        return false;
    }

    //if they're not the same, then we have diff solutions
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (table3[i][j] != table2[i][j]) {
                sudokuTable_delete(s2);
                sudokuTable_delete(s3);
                return false;
            }
        } 
    } 

    //otherwise they're the same
    sudokuTable_delete(s2);
    sudokuTable_delete(s3);
    return true;

} //end checkUniqueness

/******************* checkUniqueness() ******************/
/* see creator.h for more information */
void randomize(int* arr, int dimension) {
    // randomize time
    srand(time(NULL));

    int tmp = 0;
    int x = 0;
    int y = 0;

    // randomize an array
    for (int i = 0; i < 20; i++) {
        x = rand() % dimension;
        y = rand() % dimension;
        tmp = arr[x];
        arr[x] = arr[y];
        arr[y] = tmp;
    } 

} 

/******************* backtrackRand() ******************/
/* see creator.h for more information */
bool backtrackRand(int** board, int r, int c, bool** row, bool** col, bool*** boxes, int dimension, int* arr) {
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
        randomize(arr, dimension);
        for (int i = 0; i < dimension; i++) {
            int num = arr[i];
            //only if it adheres to sudoku rules
            if (!(row[r][num] || col[c][num] || boxes[r / (int)(sqrt(dimension))][c / (int)(sqrt(dimension))][num])) {
                //now if we come across a valid candidate, insert it into the board and try to progress
                row[r][num] = true;
                col[c][num] = true;
                boxes[r / (int)(sqrt(dimension))][c / (int)(sqrt(dimension))][num] = true;
                board[r][c] = num;

                //so we recur onto next slot and see if our candidate from above is valid
                if (backtrackRand(board, r, c + 1, row, col, boxes, dimension, arr)) {
                    return true;
                }

                //we reset our board so we don't disrupte backtracking from other slots
                board[r][c] = 0;
                row[r][num] = false;
                col[c][num] = false;
                boxes[r / (int)(sqrt(dimension))][c / (int)(sqrt(dimension))][num] = false;
            }
        }
    } 

    //already a number so move on
    else {
        return backtrackRand(board, r, c + 1, row, col, boxes, dimension, arr);
    }

    return false;
} //end backtrack


