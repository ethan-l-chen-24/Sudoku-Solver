/* 
 * fuzztester.c - generates n unique, hard-level boards and solves them, checking for uniqueness and
 *                whether the solved board follows the rules of Sudoku or not
 *
 * usage: ./fuzztester n dimension
 * where, 
 *          n is the number of boards to generate
 *          dimension is the dimension for each of the n boards
 * 
 * Bansharee Ireen, Jeffrey Jiang, Ethan Chen
 * 
 * Nov 9, 2021
 * CS50, Fall 2021
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sudokuTable.h"
#include "creator.h"
#include "solver.h"

#ifdef FUZZTEST

// function prototypes
bool changedNum(sudokuTable_t* created, sudokuTable_t* solved, int dimension);
bool isRepeat(sudokuTable_t* sudoku, int dimension);


int main(const int argc, char* argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments. Usage: ./fuzztester n dimensions\n");
        return 1;
    }

    // the number of boards to create
    char* c = argv[1];
    int num = atoi(c);

    // the dimension
    int dimension = atoi(argv[2]);

    sudokuTable_t* sudoku;
    for (int n = 0; n < num; n++) {
        // create n tables on hard mode, i.e. start with 25 given numbers
        sudoku = generateUniqueTable(25, dimension);

        // print the original board for user to see
        printf("\nPrinting the created table...\n");
        sudokuTable_print(stdout, sudoku, true);

        // print the original board to a file to be read by loading function
        FILE* fp = fopen("../tables/table3.txt", "w");
        sudokuTable_print(fp, sudoku, true);
        fclose(fp);
        
        // create a copy of the original board to solve
        FILE* fp1 = fopen("../tables/table3.txt", "r");
        sudokuTable_t* solve = sudokuTable_load(fp, dimension);
        fclose(fp1);

        // solve the copy
        solveSudoku(solve, 1, 9);
        printf("\nPrinting the solved board...\n");
        sudokuTable_print(stdout, solve, true);

        // check if created board was unique
        if (!checkUniqueness(sudoku, dimension)) {
            printf("Failed! Created board is not unique.\n");
            return 3;
        } else {
            printf("Success! Created board is unique.\n");
        }

        // check if solve changed the starting numbers in the grid
        if (changedNum(sudoku, solve, dimension)) {
            printf("Failed! Solver changed the starting numbers.\n");
            return 4;
        } else {
            printf("Success! Solver did not change the original board's starting numbers.\n");
        }

        // check if the numbers follow the rules of sudoku
        if (isRepeat(solve, dimension)) {
            printf("Failed! Solved board does not follow the rules of Sudoku.\n");
            return 5;
        } else {
            printf("Success! Solved board follows the rules of Sudoku.\n");
        }
        sudokuTable_delete(sudoku);
        sudokuTable_delete(solve);
        printf("____________________________________\n");
    }
}

bool changedNum(sudokuTable_t* created, sudokuTable_t* solved, int dimension) {
    // get boards for the original sudoku and the solved one
    int** ogBoard = sudokuTable_board(created);
    int** newBoard = sudokuTable_board(solved);

    // loop through the cells
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
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

bool isRepeat(sudokuTable_t* sudoku, int dimension) {
    int** board = sudokuTable_board(sudoku);    
    //these will hold which numbers are in each row, col, and box. So if the number 5 is at coordinates (i, j), then row[i][5] = true denoting there is a 5 in row i. 
    //like wise, col[j][5] = true, and boxes[i/3][j/3][5] = true.
    bool row[dimension][dimension+1];
    bool col[dimension][dimension+1];

    // the square root of the dimension
    int sqrtDim = sqrt(dimension);
    bool boxes[sqrtDim][sqrtDim][dimension+1];
    int num=0;

    //initalizing everything to false
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension+1; j++){
            row[i][j]=false;
            col[i][j]=false;
        }
    }

    //initalizing everything to false
    for(int i = 0; i < sqrtDim; i++){
        for(int j = 0; j < sqrtDim; j++){
            for(int k = 0; k < dimension+1; k++){
                boxes[i][j][k]=false;
            }       
        }       
    }

    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
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