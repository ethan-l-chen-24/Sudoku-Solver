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
#include "creator.h"
#include "solver.h"
#include "sudokuTable.h"

//#ifdef UNITTEST

int test1() 
{
    int failed = 0;

    sudokuTable_t* sudoku = sudokuTable_new(9);
    sudokuTable_set(sudoku, 0, 0, 3);
    sudokuTable_set(sudoku, 0, 1, 5);
    sudokuTable_set(sudoku, 0, 2, 7);
    sudokuTable_set(sudoku, 1, 0, 2);
    sudokuTable_set(sudoku, 1, 1, 8);
    sudokuTable_set(sudoku, 1, 2, 4);
    sudokuTable_set(sudoku, 2, 0, 9);
    sudokuTable_set(sudoku, 2, 1, 1);
    sudokuTable_set(sudoku, 2, 2, 6);

    if(sudoku == NULL) failed++;
    if(sudokuTable_get(sudoku, 0, 0) != 3) failed++; 
    if(sudokuTable_get(sudoku, 0, 1) != 5) failed++; 
    if(sudokuTable_get(sudoku, 2, 0) != 9) failed++;

    sudokuTable_delete(sudoku);
    if(sudoku != NULL) failed++; 
    swapRow(sudoku, 0, 1);
    swapRow(sudoku, 0, 2);
    swapRow(sudoku, 1, 2);

    return failed;
}

int test2() 
{
    
}

int test3() 
{
    
}

int test4() 
{
    
}

int main(int argc, char const *argv[])
{
    int totalFailed = 0;

    int failed = 0;
    printf("Welcome to Unit Testing\n");
    failed += test1();
    if (failed == 0) {
        printf("Test 1 passed\n");
    } else {
        printf("Test 1 failed!\n");
        totalFailed++;
    }

    int failed = 0;
    printf("Welcome to Unit Testing\n");
    failed += test2();
    if (failed == 0) {
        printf("Test 2 passed\n");
    } else {
        printf("Test 2 failed!\n");
        totalFailed++;
    }

    int failed = 0;
    printf("Welcome to Unit Testing\n");
    failed += test3();
    if (failed == 0) {
        printf("Test 3 passed\n");
    } else {
        printf("Test 3 failed!\n");
        totalFailed++;
    }

    int failed = 0;
    printf("Welcome to Unit Testing\n");
    failed += test4();
    if (failed == 0) {
        printf("Test 4 passed\n");
    } else {
        printf("Test 4 failed!\n");
        totalFailed++;
    }

    if(totalFailed > 0) {
        fprintf(stderr, "Unit testing failed T_T\n");
        return 1;
    } else {
        printf("All tests passed!\n");
        return 0;
    }
}

#endif
