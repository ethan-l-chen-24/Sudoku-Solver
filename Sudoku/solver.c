
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

//function prootypes
void solveSudoku(int board[9][9]);
bool backtrack(int board[9][9], int r, int c,  bool row[9][10], bool col[9][10], bool boxes[3][3][10]);


int main(){
    int arr[9][9] = 
    {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    // int arr[9][9] = 
    // {
    //     {1,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0,0,0}
    // };

    solveSudoku(arr);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

}//end main


void solveSudoku(int board[9][9]){
    bool row[9][10];
    bool col[9][10];
    bool boxes[3][3][10];
    int num=0;
    
    for(int i=0;i<9;i++){
        for(int j=0;j<10;j++){
            row[i][j]=false;
            col[i][j]=false;
        }
    }
    
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            for(int k=0;k<10;k++)
                boxes[i][j][k]=false;
    
    
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(board[i][j]==0) continue;
            num=board[i][j];
            row[i][num]=true;
            col[j][num]=true;
            boxes[i/3][j/3][num]=true;
        }
    }
    backtrack(board,0,0,row,col,boxes);
}//end solve

bool backtrack(int board[9][9], int r, int c,  bool row[9][10], bool col[9][10], bool boxes[3][3][10]){
    if(c==9){
        c=0;
        r++;
        if(r==9)
            return true;
    }
    if(board[r][c]==0){
        for(int num=1;num<=9;num++){
            if(!(row[r][num]||col[c][num]||boxes[r/3][c/3][num])){
                row[r][num]=true;
                col[c][num]=true;
                boxes[r/3][c/3][num]=true;
                board[r][c]=num;
                if(backtrack(board,r,c+1,row,col,boxes)) return true;
                board[r][c]=0;
                row[r][num]=false;
                col[c][num]=false;
                boxes[r/3][c/3][num]=false;
            }
        }
    }//end if
    
    
    else return backtrack(board,r,c+1,row,col,boxes);
    
    return false;
}//end backtrack