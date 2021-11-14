# Final Project - Jeffrey Jiang, Bansharee Ireen, Ethan Chen
## Sudoku Solver, CS50 Fall 2021

## Data Structures Used

### `sudokuTable_t`

A struct to hold a sudoku table, represented by an `int** table` data member of `int dimensions`. This is implemented in `sudokuTable.h`. It contains all functionality necessary to create, delete, print, load, or edit a sudoku table.

### `validator_t`

A struct to hold three matrices, a `bool** row`, a `bool** col`, and a `bool*** boxes`. For `row`, the occurrence of each number in each row is stored, while for `col`, the occurrence of each number in each column is stored. Finally, for `boxes`, the occurrence of each number in each 3x3 sub-box in the sudoku table is stored. The first index of reach represents which row/column is being accessed while the second index represents the occurrence of the specific number. For `boxes`, the boxes are imagined on a 3x3 grid, where the first index is the row, the second the column, and the last the number. Thus, the sizes of `row`, `col`, and `boxes` will be `[9][10]`, `[9][10]`, and `[3][3][10]` respectively, on a 9x9 grid. For a generic grid, it will be `[dimension][dimension + 1]`, `[dimension][dimension + 1]`, and `[sqrt(dimension)][sqrt(dimension)][dimension + 1]`.

## Detailed Pseudocode

### Psuedocode for `creator.c`

`generateUniqueTable`

1. Create a pointer to a `struct sudokuTable` by calling `generate`
2. while that struct fails `checkUniqueness`
    1. delete that struct
    2. generate a new one
3. return the struct

`generate`

1. Loads in a sudoku table from sudoku struct
2. Create `boolean` matrices `row`, `col`, and `boxes` to keep track of whether a particular cell contains a particular number
3. Initialize all entries in matrices to false
4. While we have not generated the specified amount of numbers
    1. Randomly generate a coordinate on the sudoku table along with a randomly generated integer between 1 and 9
5. Return the sudoku board with the generated sudoku board

`checkUniqueness`

1. Get two boards for the parameter `sudokuTable_t* sudoku`
2. Solve both boards using `solveSudoku` with `direction` 1 and then `direction` -1
3. Loop through the cells of the board
    1. Check if the solved boards are the same; if not, `return false`
4. `return true`

### Psuedocode for `solver.c`

`solveSudoku`

1. Grab the `board` from the `sudokuTable_t* sudoku` parameter
2. Create `boolean` matrices `row`, `col`, and `boxes` to keep track of whether a particular cell contains a particular number
3. Create `int num` to hold the number in any cell
4. Loop through the cell of the matrices to initialize them as false
5. Loop through row and columns of `board`
    1. If cell is empty, `continue` to next cell
    2. Set `num` to the number at the cell
    3. Check for invalid entries at row, column, and a 3x3 box
    4. If not invalid, set the value of the `boolean` matrices at that cell to true
6. If not invalid,
    1. If `direction` parameter is set to 1, use `backtrack` to set a valid number in each cell on the board
    2. Else, use `backtrackRev` to grab another solved board
7. Else, print error message saying the board is invalid

`backTrack`

1. Check if parameter `int c` is at max number of columns
    1. Set the column `c` to 0
    2. Move to next row
    3. `return true` if parameter for row `int r` is at max number of rows
2. If the current cell at row `r` and column `c` is empty
    1. Loop through all the possible values in increasing order
        1. Check if the number adheres to sudoku rules
            1. Set the `boolean` matrices `row`, `col`, and `boxes` to `true` for that cell
            2. Recursively move on to the next cell
            3. Reset the `boolean` matrices to false for the cell
3. Else, if the there is already a number at the cell, recursively move on to the next cell
4. `return false`

`backtrackRev`

1. Check if parameter `int c` is at max number of columns
    2. Set the column `c` to 0
    3. Move to next row
    4. `return true` if parameter for row `int r` is at max number of rows
2. If the current cell at row `r` and column `c` is empty
    1. Loop through all the possible values in decreasing order
        1. Check if the number adheres to sudoku rules
            1. Set the `boolean` matrices `row`, `col`, and `boxes` to `true` for that cell
            2. Recursively move on to the next cell
            3. Reset the `boolean` matrices to false for the cell
3. Else, if the there is already a number at the cell, recursively move on to the next cell
4. `return false`

### Psuedocode for `validator.c`

`validator_new`

1. allocate space for the `validator_t` struct
2. allocate space for the `row`, `col`, and `boxes` matrices
3. set the `row`, `col`, and `boxes` as the properties of the struct
4. return the struct

`validator_delete`

1. free the insides of each matrix
2. free the `row`, `col`, and `boxes` pointers
3. free the `validator_t` pointer


### Psuedocode for `sudoku.c`

`main`

1. Validate there are exactly 3 arguments, otherwise throw error
2. Validate each parameter using `validateParam`
3. If in create mode, call `createTable`, otherwise call `solveTable`

`validateParam`

1. Check that the `mode` param is equal to either _”create”_ or _”solve”_, otherwise throw errors
2. Check that the `difficulty` param is equal to either _”easy”_ or _”hard”_, otherwise throw errors

`createTable`

1. Create a new `sudokuTable_t* sudoku` using `generateTable` described in `creator.h`
2. On that `sudokuTable_t* sudoku` call `sudokuTable_print` described in `sudokuTable.h`

`solveTable`

1. Load the `sudokuTable_t* sudoku` using `sudokuTable_load` described in `sudokuTable.h`
2. On the `sudokuTable_t* sudoku` call `solveSudoku` described in `solver.h`
3. Call `sudokuTable_print` described in `sudokuTable.h` to print the solved board

### Pseudocode for `sudokuTable.c`

`sudokuTable_new`

1. Allocate memory for `sudokuTable_t* sudoku` the size of a `sudokuTable_t`
2. Allocate memory for an integer 2D array `int** matrix`, and allocate memory for `int*` arrays that can hold `dimension` ints each
3. Insert those arrays into `matrix` at each of the 9 indices
4. Set `matrix` as the table of `sudoku`, and parameter `dimension` as the dimension of `sudoku`
5. Return `sudoku`

`sudokuTable_board`

1. Return the `table` or `sudokuTable_t* sudoku` given as a parameter

`sudokuTable_load`

1. Create a new `sudokuTable_t* sudoku` using `sudokuTable_new`
2. Set variables `row` and `col` to 0
3. While not reading the end of `FILE* fp`
    1. While not reading the line-break character
    2. If the character is a digit
        1. Set the digit as the current `row` and `col` in the `sudoku`
        2. Increment `col`
    3. Increment `row`
    4. Set `col` to 0

`sudokuTable_set`

1. Grab the `int**` table from `sudokuTable_t* sudoku`
2. Set the value at `row`, `col` to `val`

`sudokuTable_get`

1. Grab the `int**` table from `sudokuTable_t* sudoku`
2. Return the value at `row`, `col`

`sudokuTable_delete`

1. Loop through all of the rows in the `int** table` of `sudokuTable_t* sudoku`
    1. Free the memory of each row
2. Free the `table`
3. Free the `sudoku`

`sudokuTable_print`

1. Grab the `int**` table from `sudokuTable_t* sudoku`
2. If `style` is false
    1. Loop through every `row`
        1. Loop through every `column`
            1. Print the value of the cell at `row`, `col`
        2. Print a linebreak
3. Else
    1. Create a `rowCount` and `columnCount` variables to keep track of which row and column we are on
    2. Loop through every `row`
        1. Loop through every `column`
            1. Print the value of the cell at `row`, `col`
            2. Increment `columnCount`
            3. If `columCount` is divisible by three, print a `|`
        2. Increment `rowCount`
        3. If `rowCount` is divisible by three, `printRowBar`
        4. Else print a linebreak followed by `|`

## Function Prototypes

### Functions for `creator.c`

```c
sudokuTable_t* generateUniqueTable(int numFilled, int dimension);
sudokuTable_t* generate(int numFilled, int dimension);
bool checkUniqueness(sudokuTable_t* sudoku, int dimension);
```

### Functions for `solver.c`

```c
void solveSudoku(sudokuTable_t* sudoku, int direction);
bool backtrack(sudokuTable_t* sudoku, int r, int c,  bool row[9][10], bool col[9][10], bool boxes[3][3][10]);
bool backtrackRev(sudokuTable_t* sudoku, int r, int c,  bool row[9][10], bool col[9][10], bool boxes[3][3][10]);
bool isSolved(sudokuTable_t* sudoku, int dimension);
validator_t* validator_new(int dimension);
void validator_delete(validator_t* val);
```

### Functions for `sudokuTable.c`

```c
sudokuTable_t* sudokuTable_new(int dimension);
int** sudokuTable_board(sudokuTable_t* sudoku);
int sudokuTable_dimension(sudokuTable_t* sudoku);
sudokuTable_t* sudokuTable_load(FILE* fp, int dimension);
void sudokuTable_set(sudokuTable_t* sudoku, int row, int col, int val);
int sudokuTable_get(sudokuTable_t* sudoku, int row, int col);
void sudokuTable_delete(sudokuTable_t* sudoku);
void sudokuTable_print(FILE* fp, sudokuTable_t* sudoku, bool style);
static bool validVal(sudokuTable_t* sudoku, int val);
static bool validInd(sudokuTable_t* sudoku, int ind);
static void printRowBar(void);
```

### Functions for `sudoku.c`

```c
void validateParam(char* mode, char* difficulty);
void createTable(char* difficulty);
void solveTable();
int fileno(FILE *stream);
```

## Error Handling

### For handling errors, the functions either

1. print out an error message, perform a non-zero exit within the function, killing the program,
2. print out an error message, return a non-zero value to main which then returns with a non-zero value, killing the program,
3. print out an error message but continue to the next task.
