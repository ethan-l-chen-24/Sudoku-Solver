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
#include <stdbool.h>
#include "creator.h"
#include "sudokuTable.h"
#include "solver.h"

/******************* generateUniqueTable() ******************/
/* see creator.h for more information */
sudokuTable_t* generateUniqueTable(int numFilled) {
   
   // keep on generating until it is unique
   sudokuTable_t* sudokuTable = NULL;
    while(!checkUniqueness(sudokuTable)) {
        sudokuTable = generate(numFilled);
    }
    return sudokuTable;
}//end generateTable

/******************* generate() ******************/
/* see creator.h for more information */
sudokuTable_t* generate(int numFilled) {
    sudokuTable_t* sudoku = sudokuTable_new(9);
    if(sudoku == NULL) return;
    
    int** board = sudokuTable_board(sudoku);
    bool row[9][10];
    bool col[9][10];
    bool boxes[3][3][10];
    int num=0;
    
    //initalizing everything to false
    for(int i=0;i<9;i++){
        for(int j=0;j<10;j++){
            row[i][j]=false;
            col[i][j]=false;
        }//end inner for
    }//end for
    
    //initalizing everything to false
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<10;k++){
                boxes[i][j][k]=false;
            }//end inner for
                
        }//end middle for
            
    }//end outer for
    
    int n=numFilled;
    int x=0;
    int y=0;

    while(n>0){
        //generate random coordiates on the sudoku board
        x = rand()%9;
        y = rand()%9;

        //generate a random number between 1-9
        num = (rand() % 9) +1;
        

        //if we can the insertion of the random number into the random coordinate is valid, then do it
        if(!row[x][num] && !col[y][num] && !boxes[x/3][y/3][num] && !board[x][y]){
            row[x][num]=true;
            col[y][num]=true;
            boxes[x/3][y/3][num]=true;
            board[x][y] = num;
            n--;
        }//end if
        

    }//end while

    return sudoku;
}

//returns true if sudoku board is unique
//returns false if there are multiple solutions detected
/* see creator.h for more information */
bool checkUniqueness(sudokuTable_t* sudoku){
    if(sudoku == NULL) return false;
    int** table1 = sudokuTable_board(sudoku);
    sudokuTable_t* s2 = sudokuTable_new(9);
    sudokuTable_t* s3 = sudokuTable_new(9);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            sudokuTable_set(s2, i, j, table1[i][j]);
            sudokuTable_set(s3, i, j, table1[i][j]);
        }//end inner for
    }//end for
    int** table2 = sudokuTable_board(s2);
    int** table3 = sudokuTable_board(s3);
    
    
    //get two sudoku boards, one with foward and the other with rev backtrack 
    solveSudoku(s3, 1);
    solveSudoku(s2, -1);
    
    //if they're not the same, then we have diff solutions
    for(int i=0;i<0;i++){
        for(int j=0;j<9;j++){
            if(table3[i][j] != table2[i][j]){
                return false;
            }//end if

        }//end inner for
    }//end outer for

    //otherwise they're the same

    sudokuTable_delete(s2);
    sudokuTable_delete(s3);
    return true;

}//end checkUniqueness

