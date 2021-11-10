
/*
 * solver.c : attempts to solve a sodoku board
 *
 * 
 * Bansharee Ireen, Ethan Chen, Jeffrey Jiang
 * Nov 4, 2021
 * 
 * CS50, Fall 2021
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "solver.h"
#include "sudokuTable.h"

//function prootypes


// int main(){
//     // int arr[9][9] = 
//     // {
//     //     {5,3,0,0,7,0,0,0,0},
//     //     {6,0,0,1,9,5,0,0,0} ,
//     //     {0,9,8,0,0,0,0,6,0},
//     //     {8,0,0,0,6,0,0,0,3},
//     //     {4,0,0,8,0,3,0,0,1},
//     //     {7,0,0,0,2,0,0,0,6},
//     //     {0,6,0,0,0,0,2,8,0},
//     //     {0,0,0,4,1,9,0,0,5},
//     //     {0,0,0,0,8,0,0,7,9}
//     // };

//     // int arr[9][9] = 
//     // {
//     //     {1,0,0,0,0,0,0,0,0},
//     //     {0,0,0,0,0,0,0,0,0},
//     //     {0,0,0,0,0,0,0,0,0},
//     //     {0,0,0,0,0,0,0,0,0},
//     //     {0,0,0,0,0,0,0,0,0},
//     //     {0,0,0,0,0,0,0,0,0},
//     //     {0,0,0,0,0,0,0,0,0},
//     //     {0,0,0,0,0,0,0,0,0},
//     //     {0,0,0,0,0,0,0,0,0}
//     // };
//     //sudokuTable_t* s = sudokuTable_new(9);

//     //solveSudoku(s, 1);
//     // for(int i=0;i<9;i++){
//     //     for(int j=0;j<9;j++){
//     //         printf("%d ", arr[i][j]);
//     //     }
//     //     printf("\n");
//     // }

// }//end main


/* see solver.h for more information */
//for direction: 1 means increasing order (use by default), -1 means decreasing order
bool solveSudoku(sudokuTable_t* sudoku, int direction, int dimension){

    int sqrtDimension = sqrt(dimension);
    
    if(sudoku == NULL) {
        return false;
    }

    int** board = sudokuTable_board(sudoku);
    
    //these will hold which numbers are in each row, col, and box. So if the number 5 is at coordinates (i, j), then row[i][5] = true denoting there is a 5 in row i. 
    //like wise, col[j][5] = true, and boxes[i/3][j/3][5] = true.
    
    bool** row = calloc(dimension, sizeof(bool*));
    for(int i=0;i<dimension;i++){
        row[i] = (bool*)calloc(dimension+1, sizeof(bool));
    }

    bool** col = calloc(dimension, sizeof(bool*));
    for(int i=0;i<dimension;i++){
        col[i] = (bool*)calloc(dimension+1, sizeof(bool));
    }

    bool*** boxes = calloc(sqrtDimension, sizeof(bool**));
    for(int i=0;i<sqrtDimension;i++){
        boxes[i] = (bool**) calloc(sqrtDimension, sizeof(bool*));
        for(int j=0;j<dimension+1;j++){
            boxes[i][j] = (bool*) calloc(dimension+1, sizeof(bool));
        }
    }

    int num=0;
    bool invalid = false;
    
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
        
    
    //now we start setting numbers to true given what's already on the board. This will also check for invalid entries while it's filling in. 
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if(board[i][j]==0) continue;
            num=board[i][j];
            if(row[i][num]){invalid=true; fprintf(stderr, "%d already exists in row\n", num);} 
            else row[i][num] = true;

            if(col[j][num]){invalid=true; fprintf(stderr, "%d already exists in col\n", num);} 
            else col[j][num]=true;

            if(boxes[i/sqrtDimension][j/sqrtDimension][num]){invalid=true; fprintf(stderr, "%d already exists in box\n", num);} 
            else boxes[i/sqrtDimension][j/sqrtDimension][num]=true;
        }
    }

    if(!invalid){
        
        if(direction==1){ backtrack(board,0,0,row,col,boxes, dimension);}

        else backtrackRev(board,0,0,row,col,boxes, dimension);

        if(!isSolved(sudoku, dimension)) {
            return false;
        }
        return true;
    
    }//end if
    else {
        fprintf(stderr, "Invalid board\n");
        return false;
    }
    


}//end solve


//backtracking algo: it will recur along columns first, and then move along the rows. 
/* see solver.h for more information */
bool backtrack(int** board, int r, int c,  bool** row, bool** col, bool*** boxes, int dimension){    
    //if we succesfully filled a whole column
    if(c==dimension){
        c=0;
        //move onto the next row
        r++;

        //we have all cols from the top left so we are done
        if(r==dimension){
            return true;
        }//end if
            
    }//end if

    //if there is an empty space
    if(board[r][c]==0){

        //we try all numbers
        for(int num=1;num<=dimension;num++){
            
            //only if it adheres to sudoku rules
            if(!(row[r][num]||col[c][num]||boxes[r/ (int)(sqrt(dimension))][c/ (int)(sqrt(dimension))][num])){
                //now if we come across a valid candidate, insert it into the board and try to progress
                row[r][num]=true;
                col[c][num]=true;
                boxes[r/ (int)(sqrt(dimension))][c/ (int)(sqrt(dimension))][num]=true;
                board[r][c]=num;
                
                //so we recur onto next slot and see if our candidate from above is valid
                if(backtrack(board,r,c+1,row,col,boxes, dimension)) return true;
                
                //we reset our board so we don't disrupte backtracking from other slots
                board[r][c]=0;
                row[r][num]=false;
                col[c][num]=false;
                boxes[r/ (int)(sqrt(dimension))][c/ (int)(sqrt(dimension))][num]=false;
            }
        }
    }//end if
    
    //already a number so move on
    else return backtrack(board,r,c+1,row,col,boxes, dimension);
    
    return false;
}//end backtrack

/* see solver.h for more information */
bool backtrackRev(int** board, int r, int c,  bool** row, bool** col, bool*** boxes, int dimension){
    if(c==dimension){
        c=0;
        r++;
        if(r==dimension)
            return true;
    }
    if(board[r][c]==0){
        for(int num=dimension;num>=1;num--){
            if(!(row[r][num]||col[c][num]||boxes[r/ (int)(sqrt(dimension))][c/ (int)(sqrt(dimension))][num])){
                row[r][num]=true;
                col[c][num]=true;
                boxes[r/ (int)(sqrt(dimension))][c/ (int)(sqrt(dimension))][num]=true;
                board[r][c]=num;
                if(backtrackRev(board,r,c+1,row,col,boxes, dimension)) return true;
                board[r][c]=0;
                row[r][num]=false;
                col[c][num]=false;
                boxes[r/ (int)(sqrt(dimension))][c/ (int)(sqrt(dimension))][num]=false;
            }
        }
    }//end if
    
    
    else return backtrackRev(board,r,c+1,row,col,boxes, dimension);
    
    return false;
}//end backtrack

/* see solver.h for more information */
bool isSolved(sudokuTable_t* sudoku, int dimension) {
    int** board = sudokuTable_board(sudoku);
    for(int row = 0; row < dimension; row++) {
        for(int col = 0; col < dimension; col++) {
            if(board[row][col] == 0) {
                return false;
            }
        }
    }
    return true;
}

