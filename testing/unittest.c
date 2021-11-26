/*
 * unittest.c - unittests sudoku methods
 *
 * usage: ./unittest
 * 
 * Bansharee Ireen, Ethan Chen, Jeffrey Jiang
 * Nov 4, 2021
 * 
 * CS50, Fall 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "creator.h"
#include "solver.h"
#include "../sudoku/sudokuTable.h"

// test for sudoku table struct
int test_new() {
    // the number of errors
    int failed = 0;

    // create a new table
    sudokuTable_t * sudoku = sudokuTable_new(9, true);

    // set numbers to certain cells
    sudokuTable_set(sudoku, 0, 3, 3);
    sudokuTable_set(sudoku, 0, 4, 5);
    sudokuTable_set(sudoku, 0, 5, 7);
    sudokuTable_set(sudoku, 1, 3, 2);
    sudokuTable_set(sudoku, 1, 4, 8);
    sudokuTable_set(sudoku, 1, 5, 4);
    sudokuTable_set(sudoku, 2, 3, 9);
    sudokuTable_set(sudoku, 2, 4, 1);
    sudokuTable_set(sudoku, 2, 5, 6);

    // print the table
    sudokuTable_print(stdout, sudoku);

    // check if sudoku is NULL
    if (sudoku == NULL) {
        failed++;       // if so, increment number of errors
    }
    // check if we can get back the numbers we inputted earlier
    if (sudokuTable_get(sudoku, 0, 3) != 3) {
        failed++;
    }
    if (sudokuTable_get(sudoku, 0, 4) != 5) {
        failed++;
    }
    if (sudokuTable_get(sudoku, 2, 3) != 9) {
        failed++;
    }

    sudokuTable_delete(sudoku);

    return failed;
}

// test for creating a sudoku table
int test_create() {
    int failed = 0;

    // create a full table and print it
    sudokuTable_t* sudoku = createUniqueTable(25, 9);
    sudokuTable_print(stdout, sudoku);

    // check if creation was successful
    if (sudoku == NULL) failed++;

    // check if the number is in the row
    int randomCell = sudokuTable_get(sudoku, 0, 0);
    for (int i = 1; i < 9; i++) {
        if (sudokuTable_get(sudoku, 0, i) == randomCell) {
            failed++;
        }
    }

    // check if it is in the column
    for (int i = 1; i < 9; i++) {
        if (sudokuTable_get(sudoku, i, 0) == randomCell) {
            failed++;
        }
    }

    // check if it is in the 3x3 box
    for (int i = 1; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudokuTable_get(sudoku, i, j) == randomCell) {
                failed++;
            }
        }
    }

    sudokuTable_delete(sudoku);

    return failed;
}

// test for loading a sudoku before solve
int test_load() {
    int failed = 0;

    // create a new sudoku table
    sudokuTable_t * ogSudoku = createUniqueTable(25, 9);
    if (ogSudoku == NULL) {
        failed++;
    }

    // print table for user to see
    printf("Printing the original table...\n");
    sudokuTable_print(stdout, ogSudoku);

    // print table WITH grids into a file that will only be read by the loading function
    FILE * fp1 = fopen("../tables/loadtest.txt", "w");
    if (fp1 != NULL) {
        sudokuTable_print(fp1, ogSudoku);
    }
    fclose(fp1);

    // load the table from the file
    FILE * fp2 = fopen("../tables/loadtest.txt", "r");
    sudokuTable_t * loadedSudoku;
    if (fp2 != NULL) {
        loadedSudoku = sudokuTable_load(fp2, 9);
    }
    fclose(fp2);

    // print loaded table for user to see
    printf("Printing the loaded table...\n");
    sudokuTable_print(stdout, loadedSudoku);

    // get the boards from the sudoku structs
    int ** ogBoard = sudokuTable_board(ogSudoku);
    int ** loadedBoard = sudokuTable_board(loadedSudoku);

    // compare the loaded table with the original table
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) { 
            // if they are not the same
            if (ogBoard[i][j] != loadedBoard[i][j]) {
                printf("Failed load test! Loaded table is incorrect.\n");
                
                // delete the boards
                sudokuTable_delete(ogSudoku);
                sudokuTable_delete(loadedSudoku);

                // increment number of errors
                failed++;
                return failed;
            }
        }
    }

    // delete the boards
    sudokuTable_delete(ogSudoku);
    sudokuTable_delete(loadedSudoku);

    return failed;
}

// testing that create creates a unique table
int test_uniqueness() {
    int failed = 0;

    sudokuTable_t * s;
    sudokuTable_t * s2;

    // create a unique table
    s = createUniqueTable(25, 9);
    s2 = sudokuTable_new(9, true);
    int ** table = sudokuTable_board(s);

    // create a copy of the table
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudokuTable_set(s2, i, j, table[i][j]);
        }
    }

    // solve both boards
    solveSudoku(s, 1, 9);
    solveSudoku(s2, 0, 9);
    int ** t1 = sudokuTable_board(s);
    int ** t2 = sudokuTable_board(s2);
    // check if the boards are the same, i.e. they had the same solution
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (t1[i][j] != t2[i][j] || t1[i][j] == 0) {
                failed++;
            }
        }
    }

    // if no errors occurred
    if (failed == 0) {
        printf("Found unique solution of \n");
        sudokuTable_print(stdout, s);
    }
    
    // delete the boards
    sudokuTable_delete(s);
    sudokuTable_delete(s2);

    return failed;
}

int main(int argc, char const * argv[]) {
    // randomize time
    srand(time(NULL));
    // number of errors
    int totalFailed = 0;
    int failed = 0;

    printf("Welcome to Unit Testing\n");

    // runs test on sudokuTable_new
    failed += test_new();
    if (failed == 0) {
        printf("Test new passed\n");
    } else {
        printf("Test new failed!\n");
        totalFailed++;
    }

    // runs test on createUniqueTable
    failed = 0;
    failed += test_create();
    if (failed == 0) {
        printf("Test create passed\n");
    } else {
        printf("Test create failed!\n");
        totalFailed++;
    }

    // runs test on sudokuTable_load
    failed = 0;
    failed += test_load();
    if (failed == 0) {
        printf("Test load passed\n");
    } else {
        printf("Test load failed!\n");
        totalFailed++;
    }

    // runs test on checkUniqueness
    failed = 0;
    failed += test_uniqueness();
    if (failed == 0) {
        printf("Test uniqueness passed, check if printed tables are the same\n");
    } else {
        printf("Test uniqueness failed!\n");
        totalFailed++;
    }

    // the resulting errors
    if (totalFailed > 0) {
        fprintf(stderr, "Unit testing failed T_T\n");
        return 1;
    } else {
        printf("All tests passed!\n");
        return 0;
    }
}