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


/******************* generateTable ******************/
/* see creator.h for more information */
int generateTable() {
    int** table;                                        // the board
    int val[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};            // an array of value to input
    int ind = 0;                                        // the index of the val array

    // looping through the rows
    for (int row = 0; row < 9; row++) {

        // if this is the 1st, 4th, or 7th row
        // row should look like: [4 5 6 7 8 9 1 2 3]
        if (row == 1 || row == 4 || row == 7) {
            ind = 3;                                    // start taking values from ind 3 of the val array
        }
        // if this is the 2nd, 5th, or 8th row
        // row should look like: [7 8 9 1 2 3 4 5 6]
        else if (row == 2 || row == 5 || row == 8) {
            ind = 6;                                    // start taking values from ind 6 of the val array
        }
        // if this is the 0th, 3rd, or 6th row
        // row should look like: [1 2 3 4 5 6 7 8 9]
        else {
            ind = 0;
        }

        // looping through the columns of each row
        for (int col = 0; col < 9; col++) {

            // if we reach the end of the val array
            if (ind == 9) {
                ind = 0;    // start from the begining
            }

            table[row][col] = val[ind];
            ind++;
        }
    }

    return 0;
}
