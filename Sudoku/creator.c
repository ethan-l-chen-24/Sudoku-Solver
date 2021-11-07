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

/******************* generateTable() ******************/
/* see creator.h for more information */
sudokuTable_t* generateTable(int numFilled) {
    sudokuTable_t* sudoku = sudokuTable_new(9);
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
}//end generateTable

