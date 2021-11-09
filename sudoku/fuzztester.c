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

#ifdef FUZZTEST

// function prototypes
bool changedNum(sudokuTable_t* created, sudokuTable_t* solved);
bool isRepeat(sudokuTable_t* sudoku);


int main(const int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Need number of boards to create and solve.\n");
        return 1;
    }

    char* c = argv[1];
    int num = atoi(c);

    sudokuTable_t* sudoku;
    for (int n = 0; n < num; n++) {
        // create n tables on hard mode, i.e. start with 25 given numbers
        sudoku = generateUniqueTable(25);

        printf("Printing the created table...\n");
        sudokuTable_print(sudoku, true);
        
        // create a copy of the original board to solve
        sudokuTable_t* solve = sudokuTable_new(9);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                sudokuTable_set(solve, i, j, sudokuTable_get(sudoku, i, j));
            }
        }
        printf("Printing the solved board...\n");
        sudokuTable_print(solve, true);

        // check if created board was unique
        if (!checkUniqueness(sudoku)) {
            printf("Failed! Created board is not unique.\n");
            return 3;
        }

        // check if solve changed the starting numbers in the grid
        if (changedNum(sudoku, solve)) {
            printf("Failed! Solver changed the starting numbers.\n");
            return 4;
        }

        // check if the numbers follow the rules of sudoku
        if (isRepeat(solve)) {
            printf("Failed! Solved board does not follow the rules of Sudoku.\n");
            return 5;
        }

        sudokuTable_delete(sudoku);
        sudokuTable_delete(solve);
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

bool isRepeat(sudokuTable_t* sudoku) {
    int** board = sudokuTable_board(sudoku);    
    //these will hold which numbers are in each row, col, and box. So if the number 5 is at coordinates (i, j), then row[i][5] = true denoting there is a 5 in row i. 
    //like wise, col[j][5] = true, and boxes[i/3][j/3][5] = true.
    bool row[9][10];
    bool col[9][10];
    bool boxes[3][3][10];
    int num=0;

    //initalizing everything to false
    for(int i=0;i<9;i++){
        for(int j=0;j<10;j++){
            row[i][j]=false;
            col[i][j]=false;
        }
    }

    //initalizing everything to false
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<10;k++){
                boxes[i][j][k]=false;
            }       
        }       
    }

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if (board[i][j] == 0) continue;

            num = board[i][j];

            if (row[i][num]) {
                printf("%d already exists in row\n", num);
                return true;
            } 
            else row[i][num] = true;

            if (col[j][num]) {
                printf("%d already exists in col\n", num);
                return true;
            } 
            else col[j][num] = true;

            if (boxes[i/3][j/3][num]) {
                printf("%d already exists in box\n", num);
                return true;
            } 
            else boxes[i/3][j/3][num] = true;
        }
    }

    return false;
}

#endif