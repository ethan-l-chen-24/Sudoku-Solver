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

    if(style) {
        for(int i = 0; i < dimension; i ++) {
            for(int j = 0; j < dimension; j++) {
                printf("%s ", table[i][j]);
            }
            printf("\n");
        }
    } else {

        int rowCount = 0;
        int columnCount = 0;

        printRowBar();
        printf("|");
        for(int i = 0; i < dimension; i ++) {
            for(int j = 0; j < dimension; j++) {
                columnCount++;
                printf("%s ", table[i][j]);
                if (columnCount % 3 == 0) {
                    printf("|");
                }
            }
            rowCount++;
            if(rowCount % 3 == 0) {
                printRowBar();
            }
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
    for(int i = 0; i < dimension; i++) {
        save = table[row1][i];
        table[row1][i] = table[row2][i];
        table[row2][i] = save;
    }
}

/******************* swapColumn() ******************/
/* see sudokuLib.h for more information */
void swapColumn(int** table, int dimension, int col1, int col2) 
{
    int save;
    for(int i = 0; i < dimension; i++) {
        save = table[i][col1];
        table[i][col1] = table[i][col2];
        table[i][col2] = save;
    }
}