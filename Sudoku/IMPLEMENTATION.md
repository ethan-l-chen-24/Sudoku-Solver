# Final Project - Jeffrey Jiang, Bansharee Ireen, Ethan Chen
## Sudoku Solver, CS50 Fall 20221

## Data Structures Used

### `sudokuTable_t`

A struct to hold a sudoku table, represented by an `int** table` data member of `int dimensions`. This is implemented in `sudokuTable.h`

## Detailed Pseudocode

### Psuedocode for `creator.c`

### Psuedocode for `solver.c`

### Psuedocode for `sudoku.c`

## Function Prototypes

### Functions for `creator.c`

```c
sudokuTable_t* generateTable();
```

### Functions for `solver.c`

```c
void solveSudoku(sudokuTable_t* sudoku);
bool backtrack(sudokuTable_t* sudoku, int r, int c,  bool row[9][10], bool col[9][10], bool boxes[3][3][10]);
```

### Functions for `sudoku.c`

```c
void validateParam(char* mode, char* difficulty);
void createTable(char* difficulty);
// method for solving
```

## Error Handling

### For handling errors, the functions either

1. print out an error message, perform a non-zero exit within the function, killing the program,
2. print out an error message, return a non-zero value to main which then returns with a non-zero value, killing the program,
3. print out an error message but continue to the next task.