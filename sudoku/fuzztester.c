/*
 *
 *
 * 
 * 
 * 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sudokuTable.h"
#include "creator.h"
#include "solver.h"

int main(const int argc, const char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Need number of boards to create and solve.\n");
        exit(1);
    }

    int num = argv[1];

    sudokuTable_t* sudoku;
    for (int n = 0; n < num; n++) {
        // create n tables on hard mode, i.e. start with 25 given numbers
        sudoku = generateUniqueTable(25);

        printf("Printing the created table...\n");
        sudokuTable_print(sudoku, true);
        
        sudokuTable_t* solvedSudoku = sudokuTable_load(stdin, 9);
        solveSudoku(solvedSudoku, 1);
        printf("Printing the solved board...\n");
        sudokuTable_print(solvedSudoku, true);

        // check if solve changed the starting numbers in the grid
        if (changedNum(sudoku, solvedSudoku)) {
            printf("Failed! Solver changed the starting numbers.\n");
            exit(2);
        }
        
    }
}

bool changedNum(sudokuTable_t* created, sudokuTable_t* solved) {
    int** ogBoard = sudokuTable_board(created);
    int** newBoard = sudokuTable_board(solved);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // if original board did not have a number
            if (ogBoard[i][j] == 0) {
                continue;
            } else {
                // check if the starting numbers are not present in the new board
                if (ogBoard[i][j] != newBoard[i][j]) {
                    return true;
                }
            }
        }
    }
    return false;
}