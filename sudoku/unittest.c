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
#include "sudokuTable.h"

#ifdef UNITTEST

int test1() 
{
    int failed = 0;

    sudokuTable_t* sudoku = sudokuTable_new(9);
    sudokuTable_set(sudoku, 0, 3, 3);
    sudokuTable_set(sudoku, 0, 4, 5);
    sudokuTable_set(sudoku, 0, 5, 7);
    sudokuTable_set(sudoku, 1, 3, 2);
    sudokuTable_set(sudoku, 1, 4, 8);
    sudokuTable_set(sudoku, 1, 5, 4);
    sudokuTable_set(sudoku, 2, 3, 9);
    sudokuTable_set(sudoku, 2, 4, 1);
    sudokuTable_set(sudoku, 2, 5, 6);

    sudokuTable_print(sudoku, true);

    if(sudoku == NULL) failed++;
    if(sudokuTable_get(sudoku, 0, 3) != 3) failed++; 
    if(sudokuTable_get(sudoku, 0, 4) != 5) failed++; 
    if(sudokuTable_get(sudoku, 2, 3) != 9) failed++;

    sudokuTable_delete(sudoku);

    return failed;
}

int test2() 
{
    int failed = 0;
    sudokuTable_t* sudoku = generateUniqueTable(25);
    sudokuTable_print(sudoku, true);
    if(sudoku == NULL) failed++;

    sudokuTable_delete(sudoku);

    return failed;
}

int test_load() {
    int failed = 0;
    char ch;
    printf("\nTesting sudokuTable_load...\n");

    FILE* oldFP = fopen("table0.txt", "r");

    printf("Printing the original table from file...\n");
    while(fscanf(oldFP, "%c", &ch) != EOF) {
      printf("%c", ch);
    }
    printf("\n\n");
    fclose(oldFP);

    FILE* fp = fopen("../tables/table1.txt", "r");
    sudokuTable_t* table;
    if (fp != NULL) {
        table = sudokuTable_load(fp, 9);
    }
    fclose(fp);

    // print the table we just loaded
    printf("Printing the loaded table...\n");
    if (table != NULL) {
        sudokuTable_print(table, true);
    }
    sudokuTable_delete(table);

    return failed;
}

int test4(){
    int failed=0;
    sudokuTable_t* s = generateUniqueTable(25);
    

    sudokuTable_t* s2 = sudokuTable_new(9);
    int** table = sudokuTable_board(s);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            sudokuTable_set(s2, i, j,table[i][j]);
        }
    }
    bool flag = true;
    int count=0;
    while(flag){
        s = generateUniqueTable(25);
        s2 = sudokuTable_new(9);
        table = sudokuTable_board(s);
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
            sudokuTable_set(s2, i, j,table[i][j]);
            }
        }

        solveSudoku(s, 1);
        solveSudoku(s2, 0);
        int** t1 = sudokuTable_board(s);
        int** t2 = sudokuTable_board(s2);
        count=0;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(t1[i][j]!=t2[i][j] || t1[i][j]==0){
                    count++;
                }//end if

            }//end inner for
        }//end for
        

        if(count==0)break;
        else{
            free(s);
            free(s2);
        }//end else 

    }

    printf("found unique solution of \n");
    sudokuTable_print(s, true);
    
    



    return failed;
}


int main(int argc, char const *argv[])
{
    srand(time(NULL));
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

    failed = 0;
    failed += test2();
    if (failed == 0) {
        printf("Test 2 passed\n");
    } else {
        printf("Test 2 failed!\n");
        totalFailed++;
    }

    failed = 0;
    failed += test_load();
    if (failed == 0) {
        printf("Test load passed, check if printed tables are the same\n");
    } else {
        printf("Test load failed!\n");
        totalFailed++;
    }


    test4();

    if(totalFailed > 0) {
        fprintf(stderr, "Unit testing failed T_T\n");
        return 1;
    } else {
        printf("All tests passed!\n");
        return 0;
    }
}

#endif
