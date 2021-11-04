/* 
 * sudokuLib.c - header file for 'sudokuLib' file in 'Sudoku' module
 *
 * provides a set of functions for a sudoku table, that can print, swap rows, or.....
 * 
 * Ethan Chen, Jeffrey Jiang, Bansharee Ireen, November 2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/***************** helper functions *******************/

static void printRowBar(void);

/******************* printTable() ******************/
/* see sudokuLib.h for more information */
void printTable(int** table, int dimension, bool style)
{
    if(table == NULL) return;

    // simple style, just the numbers
    if(!style) {

        // loop through every cell
        for(int i = 0; i < dimension; i ++) {
            for(int j = 0; j < dimension; j++) {
                printf("%s ", table[i][j]); // print the number
            }

            // print to next line
            printf("\n");
        }
    } else {

    // complex style, includes | and _ to explicitly show 3x3 boxes
        int rowCount = 0;
        int columnCount = 0;

        printRowBar();
        printf("|");

        // loop through every cell
        for(int i = 0; i < dimension; i ++) {
            for(int j = 0; j < dimension; j++) {
                printf("%s ", table[i][j]); // print the number

                // every three columns print a vertical bar
                columnCount++;
                if (columnCount % 3 == 0) {
                    printf("|");
                }
            }

            // every three rows print a full row of underscores
            rowCount++;
            if(rowCount % 3 == 0) {
                printRowBar();
            }

            // print next line
            printf("\n|");
        }
    }
}

/******************* swapRow() ******************/
/* print a long row bar _______________________ */
static void printRowBar(void) {
    printf("___________\n");
}

/******************* swapRow() ******************/
/* see sudokuLib.h for more information */
void swapRow(int** table, int dimension, int row1, int row2)
{
    int save;

    // loop through every column
    for(int col = 0; col < dimension; col++) {
        save = table[row1][col]; // save the row cell
        table[row1][col] = table[row2][col]; // swap the two values in each row
        table[row2][col] = save;
    }
}

/******************* swapColumn() ******************/
/* see sudokuLib.h for more information */
void swapColumn(int** table, int dimension, int col1, int col2) 
{
    int save;
    
    // loop through every row
    for(int row = 0; row < dimension; row++) {
        save = table[row][col1]; // save the column cell
        table[row][col1] = table[row][col2]; // swap the two values in each column
        table[row][col2] = save;
    }
}