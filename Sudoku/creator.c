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
    int ind = -3;                                        // the index of the val array

    // looping through the rows
    for (int row = 0; row < 9; row++) {

        // check if last index was 9, reset to 0
        if (ind  == 9) {
            ind = 0;
        }
        ind += 3;   // each row starts at val 3 indices after the last row's val

        // looping through the columns of each row
        for (int col = 0; col < 9; col++) {

            // if we reach the end of the val array
            if (ind == 9) {
                ind = 0;                // start from the begining
            }

            table[row][col] = val[ind]; // insert value
            ind++;                      // increment index
        }
    }

    return 0;
}
