
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

//local types

typedef struct validator {
    bool** row;
    bool** col;
    bool*** boxes;
    int dimension;
} validator_t;

// struct methods

/*********** validator_new **************/
/*
 * creates a new validator struct, mallocing all of the necessary memory
 *
 * caller provides: a valid dimension
 */
validator_t* validator_new(int dimension) {

    // create memory for the struct itself
    validator_t* val = malloc(sizeof(validator_t));
    if(val == NULL) return NULL;

    // allocate memory for the row matrix
    bool** row = calloc(dimension, sizeof(bool*));
    for(int i=0;i<dimension;i++){
        row[i] = (bool*)calloc(dimension+1, sizeof(bool));
    }

    // allocate memory for the col matrix
    bool** col = calloc(dimension, sizeof(bool*));
    for(int i=0;i<dimension;i++){
        col[i] = (bool*)calloc(dimension+1, sizeof(bool));
    }

    int sqrtDimension = (int) sqrt(dimension);

    // allocate memory for the boxes matrix
    bool*** boxes = calloc(sqrtDimension, sizeof(bool**));
    for(int i=0;i<sqrtDimension;i++){
        boxes[i] = (bool**) calloc(sqrtDimension, sizeof(bool*));
        for(int j=0;j<sqrtDimension;j++){
            boxes[i][j] =(bool*) calloc(dimension+1, sizeof(bool));
        }
    }

    // set each matrix to its appropriate struct property
    val->row = row;
    val->col = col;
    val->boxes = boxes;
    val->dimension = dimension;

    return val;
}

void validator_delete(validator_t* val) {
    // retrieve the matrices from the struct
    bool** row = val->row;
    bool** col = val->col;
    bool*** boxes = val->boxes;
    int dimension = val->dimension;

    // free the row and column inner-arrays
    for(int i = 0; i < dimension; i++) {
        free(row[i]);
        free(col[i]);
    }

    int sqrtDimension = (int) sqrt(dimension);

    // free the boxes inner arrays
    for(int i=0;i<sqrtDimension;i++){
        for(int j=0;j<sqrtDimension;j++){
            free(boxes[i][j]);
        }
        free(boxes[i]);
    }

    // free everythin else
    free(row); 
    free(col);
    free(boxes);
    free(val);
}

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
    
    validator_t* val = validator_new(dimension);
    bool** row = val->row;
    bool** col = val->col;
    bool*** boxes = val->boxes;

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

            if(col[j][num]){
                invalid=true; fprintf(stderr, "%d already exists in col\n", num);} 
            else col[j][num]=true;

            if(boxes[i/sqrtDimension][j/sqrtDimension][num]){invalid=true; fprintf(stderr, "%d already exists in box\n", num);} 
            else boxes[i/sqrtDimension][j/sqrtDimension][num]=true;
        }
    }

    // if the current state of the board is valid
    if(!invalid){
        
        // solve the board forwards or backwards
        if(direction==1){ backtrack(board,0,0,row,col,boxes, dimension);}

        else backtrackRev(board,0,0,row,col,boxes, dimension);

        validator_delete(val);

        // if it is solved (cells are filled in) return true;
        if(!isSolved(sudoku, dimension)) {
            return false;
        }
        
        return true;
    
    }//end if
    else {
        validator_delete(val);
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

    // if any of the cells are 0, it was not solvable
    for(int row = 0; row < dimension; row++) {
        for(int col = 0; col < dimension; col++) {
            if(board[row][col] == 0) {
                return false;
            }
        }
    }
    return true;
}

