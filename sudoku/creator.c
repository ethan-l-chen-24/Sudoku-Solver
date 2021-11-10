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
#include <math.h>
#include "creator.h"
#include "sudokuTable.h"
#include "solver.h"

/******************* generateUniqueTable() ******************/
/* see creator.h for more information */
sudokuTable_t* generateUniqueTable(int numFilled, int dimension) {
   
    // keep on generating until it is unique
    sudokuTable_t* sudokuTable = generate(numFilled, dimension);
    while(!checkUniqueness(sudokuTable, dimension)) {
        sudokuTable = generate(numFilled, dimension);
    }
    return sudokuTable;
}//end generateTable

/******************* generate() ******************/
/* see creator.h for more information */
sudokuTable_t* generate(int numFilled, int dimension) {
    sudokuTable_t* sudoku = sudokuTable_new(dimension);
    int sqrtDimension = sqrt(dimension);

    if(sudoku == NULL) return NULL;
    
    int** board = sudokuTable_board(sudoku);
    bool row[dimension][dimension+1];
    bool col[dimension][dimension+1];
    bool boxes[sqrtDimension][sqrtDimension][dimension+1];
    int num=0;
    
    //initalizing everything to false
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension+1;j++){
            row[i][j]=false;
            col[i][j]=false;
        }//end inner for
    }//end for
    
    //initalizing everything to false
    for(int i=0;i<sqrtDimension;i++){
        for(int j=0;j<sqrtDimension;j++){
            for(int k=0;k<dimension+1;k++){
                boxes[i][j][k]=false;
            }//end inner for
                
        }//end middle for
            
    }//end outer for
    
    int n=numFilled;
    int x=0;
    int y=0;

    while(n>0){
        //generate random coordiates on the sudoku board
        x = rand()%dimension;
        y = rand()%dimension;

        //generate a random number between 1-dimension
        num = (rand() % dimension) +1;
        

        //if we can the insertion of the random number into the random coordinate is valid, then do it
        if(!row[x][num] && !col[y][num] && !boxes[x/sqrtDimension][y/sqrtDimension][num] && !board[x][y]){
            row[x][num]=true;
            col[y][num]=true;
            boxes[x/sqrtDimension][y/sqrtDimension][num]=true;
            board[x][y] = num;
            n--;
        }//end if
        

    }//end while


    return sudoku;
}

//returns true if sudoku board is unique
//returns false if there are multiple solutions detected
/* see creator.h for more information */
bool checkUniqueness(sudokuTable_t* sudoku, int dimension){
    if(sudoku == NULL) return false;
    int** table1 = sudokuTable_board(sudoku);
    sudokuTable_t* s2 = sudokuTable_new(dimension);
    sudokuTable_t* s3 = sudokuTable_new(dimension);
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            sudokuTable_set(s2, i, j, table1[i][j]);
            sudokuTable_set(s3, i, j, table1[i][j]);
        }//end inner for
    }//end for
    int** table2 = sudokuTable_board(s2);
    int** table3 = sudokuTable_board(s3);
    
    
    //get two sudoku boards, one with foward and the other with rev backtrack 
    if(!solveSudoku(s3, 1, dimension)) return false;
    if(!solveSudoku(s2, 0, dimension)) return false;

    //if they're not the same, then we have diff solutions
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if(table3[i][j] != table2[i][j]) return false;
        }//end inner for
    }//end outer for

    //otherwise they're the same

    sudokuTable_delete(s2);
    sudokuTable_delete(s3);
    return true;

}//end checkUniqueness

