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
#include <time.h>
#include <pthread.h>
#include "creator.h"
#include "../solver/validator.h"
#include "../sudoku/sudokuTable.h"
#include "solver.h"

pthread_mutex_t mutexGenerate = PTHREAD_MUTEX_INITIALIZER;

/******************* generateUniqueTable() ******************/
/* see creator.h for more information */
sudokuTable_t *createUniqueTable(int numFilled, int dimension)
{
    pthread_mutex_lock(&mutexGenerate);
    sudokuTable_t *sudokuTable = generate(numFilled, dimension);
    int** table = sudokuTable_board(sudokuTable);
    int check = 0;
    bool uniq = false;
    int x=0;
    int y=0;
    int tmp=0;
    int plucks=0;
    while (!uniq)
    {

        x = rand() % dimension;
        y = rand() % dimension;

        
        if(table[x][y]!=0){
            plucks++;
            tmp = table[x][y];
            table[x][y]=0;
            if(checkUniqueness(sudokuTable, dimension)){
                check++;
            }

            else{
                table[x][y] = tmp;
            }

        }//end if

        if(plucks>=2 * (dimension*dimension)){
            sudokuTable_delete(sudokuTable);
            sudokuTable = generate(numFilled, dimension);
            table = sudokuTable_board(sudokuTable);
            plucks =0;
            check=0;
        }//end if

        if(check==(dimension*dimension) - numFilled){
            uniq = true;
        }//end if

        
    }//end while
    
    pthread_mutex_unlock(&mutexGenerate);
    return sudokuTable;
} //end generateTable

/******************* generate() ******************/
/* see creator.h for more information */
sudokuTable_t *generate(int numFilled, int dimension)
{
    sudokuTable_t *sudoku = sudokuTable_new(dimension, true);
    int sqrtDimension = sqrt(dimension);

    if (sudoku == NULL){
        return NULL;
    }
        

    int **board = sudokuTable_board(sudoku);
    validator_t* val = validator_new(dimension);
    bool** row = validator_getRow(val);
    bool** col = validator_getCol(val);
    bool*** boxes = validator_getBoxes(val);


    //initalizing everything to false
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension + 1; j++)
        {
            row[i][j] = false;
            col[i][j] = false;
        } //end inner for
    }     //end for

    //initalizing everything to false
    for (int i = 0; i < sqrtDimension; i++)
    {
        for (int j = 0; j < sqrtDimension; j++)
        {
            for (int k = 0; k < dimension + 1; k++)
            {
                boxes[i][j][k] = false;
            } //end inner for

        } //end middle for

    } //end outer for


    int arr[dimension];
    for(int i=1;i<=dimension;i++){
        arr[i-1] = i;
    }
    randomize(arr, dimension);
    backtrackRand(board,0,0,row,col,boxes, dimension, arr);
 
    return sudoku;
}

//returns true if sudoku board is unique
//returns false if there are multiple solutions detected
/* see creator.h for more information */
bool checkUniqueness(sudokuTable_t *sudoku, int dimension)
{

    if (sudoku == NULL){
        return false;
    }//end if
        
    int **table1 = sudokuTable_board(sudoku);

    // create two copies of the original board
    sudokuTable_t *s2 = sudokuTable_new(dimension, true);
    sudokuTable_t *s3 = sudokuTable_new(dimension, true);
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            sudokuTable_set(s2, i, j, table1[i][j]);
            sudokuTable_set(s3, i, j, table1[i][j]);
        } //end inner for
    }     //end for


    // grab the tables from those boards
    int **table2 = sudokuTable_board(s2);
    int **table3 = sudokuTable_board(s3);

    //get two sudoku boards, one with foward and the other with rev backtrack
    if (!solveSudoku(s3, 1, dimension))
    {
        sudokuTable_delete(s2);
        sudokuTable_delete(s3);
        return false;
    }


    if (!solveSudoku(s2, 0, dimension))
    {
        sudokuTable_delete(s2);
        sudokuTable_delete(s3);
        return false;
    }


    //if they're not the same, then we have diff solutions
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            if (table3[i][j] != table2[i][j])
            {
                sudokuTable_delete(s2);
                sudokuTable_delete(s3);
                return false;
            }
        } //end inner for
    }     //end outer for

    //otherwise they're the same
    sudokuTable_delete(s2);
    sudokuTable_delete(s3);
    return true;

} //end checkUniqueness

/* see creator.h for more information */
void randomize(int* arr, int dimension){
    srand(time(NULL));
    int tmp=0;
    int x=0;
    int y=0;
    for(int i=0;i<20;i++){
        x = rand() % dimension;
        y = rand() % dimension;
        tmp = arr[x];
        arr[x] = arr[y];
        arr[y] = tmp;
    }//end for

}//end randomize




/* see creator.h for more information */
bool backtrackRand(int** board, int r, int c,  bool** row, bool** col, bool*** boxes, int dimension, int* arr){    
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
        randomize(arr, dimension);
        for(int i=0;i<dimension;i++){
            int num = arr[i];
            //only if it adheres to sudoku rules
            if(!(row[r][num]||col[c][num]||boxes[r/ (int)(sqrt(dimension))][c/ (int)(sqrt(dimension))][num])){
                //now if we come across a valid candidate, insert it into the board and try to progress
                row[r][num]=true;
                col[c][num]=true;
                boxes[r/ (int)(sqrt(dimension))][c/ (int)(sqrt(dimension))][num]=true;
                board[r][c]=num;
                
                //so we recur onto next slot and see if our candidate from above is valid
                if(backtrackRand(board,r,c+1,row,col,boxes, dimension, arr)){
                     return true;
                }
                
                //we reset our board so we don't disrupte backtracking from other slots
                board[r][c]=0;
                row[r][num]=false;
                col[c][num]=false;
                boxes[r/ (int)(sqrt(dimension))][c/ (int)(sqrt(dimension))][num]=false;
            }
        }
    }//end if
    
    //already a number so move on
    else{
        return backtrackRand(board,r,c+1,row,col,boxes, dimension, arr);
    }
    
    return false;
}//end backtrack


