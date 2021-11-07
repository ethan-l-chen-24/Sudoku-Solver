# Final Project - Jeffrey Jiang, Bansharee Ireen, Ethan Chen
## Sudoku Solver, CS50 Fall 20221

## Data Structures Used

### `sudokuTable_t`

A struct to hold a sudoku table, represented by an `int** table` data member of `int dimensions`. This is implemented in `sudokuTable.h`. It contains all functionality necessary to create, delete, print, load, or edit a sudoku table.

## Detailed Pseudocode

### Psuedocode for `creator.c`

`generateTable()`

1. Loads in a sudoku table from sudoku struct
2. Create `boolean` matrices `row`, `col`, and `boxes` to keep track of whether a particular cell contains a particular number
3. Initialize all entries in matrices to false
4. While we have not generated the specified amount of numbers 
1. Randomly generate a coordinate on the sudoku table along with a randomly generated integer between 1 and 9. 
5. Return the sudoku board with the generated sudoku board. 



### Psuedocode for `solver.c`

`solveSudoku`

Grab the `board` from the `sudokuTable_t* sudoku` parameter
Create `boolean` matrices `row`, `col`, and `boxes` to keep track of whether a particular cell contains a particular number
Create `int num` to hold the number in any cell
Loop through the cell of the matrices to initialize them as false
Loop through row and columns of `board`
If cell is empty, `continue` to next cell
Set `num` to the number at the cell
Check for invalid entries at row, column, and a 3x3 box
If not invalid, set the value of the `boolean` matrices at that cell to true
If not invalid,
If `direction` parameter is set to 1, use `backtrack` to set a valid number in each cell on the board
Else, use `backtrackRev` to grab another solved board
Else, print error message saying the board is invalid

`backTrack`

Check if parameter `int c` is at max number of columns
Set the column `c` to 0
Move to next row
`return true` if parameter for row `int r` is at max number of rows
If the current cell at row `r` and column `c` is empty
Loop through all the possible values in increasing order
Check if the number adheres to sudoku rules
Set the `boolean` matrices `row`, `col`, and `boxes` to `true` for that cell
Recursively move on to the next cell
Reset the `boolean` matrices to false for the cell
Else, if the there is already a number at the cell, recursively move on to the next cell
`return false`

`backtrackRev`

Check if parameter `int c` is at max number of columns
Set the column `c` to 0
Move to next row
`return true` if parameter for row `int r` is at max number of rows
If the current cell at row `r` and column `c` is empty
Loop through all the possible values in decreasing order
Check if the number adheres to sudoku rules
Set the `boolean` matrices `row`, `col`, and `boxes` to `true` for that cell
Recursively move on to the next cell
Reset the `boolean` matrices to false for the cell
Else, if the there is already a number at the cell, recursively move on to the next cell
`return false`

`checkUniqueness`

Get two boards for the parameter `sudokuTable_t* sudoku`
Solve both boards using `solveSudoku` with `direction` 1 and then `direction` -1
Loop through the cells of the board
Check if the solved boards are the same; if not, `return false`
`return true`

### Psuedocode for `sudoku.c`

`main`
Validate there are exactly 3 arguments, otherwise throw error
Validate each parameter using `validateParam` 
If in create mode, call `createTable`, otherwise call `solveTable`

`validateParam`
Check that the `mode` param is equal to either _”create”_ or _”solve”_, otherwise throw errors
Check that the `difficulty` param is equal to either _”easy”_ or _”hard”_, otherwise throw errors

`createTable`
Create a new `sudokuTable_t* sudoku` using `generateTable` described in `creator.h`
On that `sudokuTable_t* sudoku` call `sudokuTable_print` described in `sudokuTable.h`

`solveTable`
Load the `sudokuTable_t* sudoku` using `sudokuTable_load` described in `sudokuTable.h`
On the `sudokuTable_t* sudoku` call `solveSudoku` described in `solver.h`
 Call `sudokuTable_print` described in `sudokuTable.h` to print the solved board

### Pseudocode for `sudokuTable.c`

`sudokuTable_new`
Allocate memory for `sudokuTable_t* sudoku` the size of a `sudokuTable_t`
Allocate memory for an integer 2D array `int** matrix`, and allocate memory for `int*` arrays that can hold `dimension` ints each
Insert those arrays into `matrix` at each of the 9 indices
Set `matrix` as the table of `sudoku`, and parameter `dimension` as the dimension of `sudoku`
Return `sudoku`

`sudokuTable_board`
Return the `table` or `sudokuTable_t* sudoku` given as a parameter

`sudokuTable_load`
Create a new `sudokuTable_t* sudoku` using `sudokuTable_new`
Set variables `row` and `col` to 0
While not reading the end of `FILE* fp`
While not reading the line-break character
If the character is a digit
Set the digit as the current `row` and `col` in the `sudoku`
Increment `col`
Increment `row`
Set `col` to 0

`sudokuTable_set`
Grab the `int**` table from `sudokuTable_t* sudoku`
Set the value at `row`, `col` to `val`

`sudokuTable_get`
Grab the `int**` table from `sudokuTable_t* sudoku`
Return the value at `row`, `col`

`sudokuTable_delete`
Loop through all of the rows in the `int** table` of `sudokuTable_t* sudoku`
Free the memory of each row
Free the `table`
Free the `sudoku`

`sudokuTable_print`
Grab the `int**` table from `sudokuTable_t* sudoku`
If `style` is false
Loop through every `row` 
Loop through every `column`
Print the value of the cell at `row`, `col`
Print a linebreak
Else 
Create a `rowCount` and `columnCount` variables to keep track of which row and column we are on
Loop through every `row`
Loop through every `column`
Print the value of the cell at `row`, `col`
Increment `columnCount`
If `columCount` is divisible by three, print a `|`
Increment `rowCount`
If `rowCount` is divisible by three, `printRowBar`
Else print a linebreak followed by `|`


## Function Prototypes

### Functions for `creator.c`

```c
sudokuTable_t* generateTable();
```

### Functions for `solver.c`

```c
void solveSudoku(sudokuTable_t* sudoku, int direction);
bool backtrack(sudokuTable_t* sudoku, int r, int c,  bool row[9][10], bool col[9][10], bool boxes[3][3][10]);
bool backtrackRev(sudokuTable_t* sudoku, int r, int c,  bool row[9][10], bool col[9][10], bool boxes[3][3][10]);
bool checkUniqueness(sudokuTable_t* sudoku);
```

### Functions for `sudokuTable.c`

```c
static bool validVal(sudokuTable_t* sudoku, int val);
static bool validInd(sudokuTable_t* sudoku, int ind);
static void printRowBar(void);
```

### Functions for `sudoku.c`
```c
void validateParam(char* mode, char* difficulty);
void createTable(char* difficulty);
```

## Error Handling

### For handling errors, the functions either

1. print out an error message, perform a non-zero exit within the function, killing the program,
2. print out an error message, return a non-zero value to main which then returns with a non-zero value, killing the program,
3. print out an error message but continue to the next task.
