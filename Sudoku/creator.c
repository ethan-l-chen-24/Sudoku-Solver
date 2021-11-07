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
#include "creator.h"
#include "sudokuTable.h"

/******************* local function ***********************/

static void randomize(sudokuTable_t* sudoku);

/******************* generateTable() ******************/
/* see creator.h for more information */
sudokuTable_t* generateTable() {
    sudokuTable_t* sudoku = sudokuTable_new(9);         // the board
    
    int start = 1;
     for (int row = 0; row < 9; row++) {
         int val = start;
        for (int col = 0; col < 9; col++) {
            if(val == 10) {
                val = 1;
            }
            sudokuTable_set(sudoku, row, col, val);
            val++;                      // increment index
        }
        start += 3;
        if(start > 9) {
            start -= 8;
        }
    }

    #ifdef UNITTEST
        sudokuTable_print(sudoku, true);
    #endif

    randomize(sudoku);
    return sudoku;
}

/******************* randomize() ******************/
/* 
 * takes a table and randomly swaps rows and columns 
 * only swaps rows and columns within the same "group"
 * groups are represented by indices 0-2, 3-5, and 6-8 for both rows and columns
*/
void randomize(sudokuTable_t* sudoku) {
    // loop through every group of 3
    for(int rowGroup = 0; rowGroup < 9; rowGroup += 3) {
        for(int colGroup = 0; colGroup < 9; colGroup += 3) {
            
            // generate two unique numbers between 0 and 2
            int randCol1 = rand() % 3;
            int randCol2 = randCol1;
            while(randCol1 == randCol2) {
                randCol2 = rand() % 3;
            }
            
            // add that value to whatever group we are currently looking at
            randCol1 += colGroup;
            randCol2 += colGroup;

            // repeate above for columns
            int randRow1 = rand() % 3;
            int randRow2 = randRow1;
            while(randRow1 == randRow2) {
                randRow2 = rand() % 3;
            }
            randRow1 += rowGroup;
            randRow2 += rowGroup;

            // swap the row and columns randomly generated
            swapColumn(sudoku, randCol1, randCol2);
            swapRow(sudoku, randRow1, randRow2);
            
        }
    }
} 