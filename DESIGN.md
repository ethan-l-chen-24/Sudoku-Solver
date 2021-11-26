# Final Project - Jeffrey Jiang, Bansharee Ireen, Ethan Chen
## Sudoku Solver, CS50 Fall 20221

### User interface

```text
./sudoku mode difficulty [dimension]
```

For example: 

```text
./sudoku create hard 9
./sudoku solve hard 9
```

### Inputs and outputs

Input: 
- _mode_: is a string which can either be `create` or `solve`. 
- _difficulty_: is a string which can either be `easy` or `hard`
- _dimension_: is a number which can be either 4, 9 or 16 (if not specified, defaults to 9). 

Output: 
If the _mode_ is set to create, then it will print to stdout a randomized sudoku puzzle with either: 
- 37 given numbers and 44 missing numbers if mode is `easy`
- 25 given numbers and 56 missing numbers if mode is `hard`

If the _mode_ is set to solve, then it will read in a valid sudoku puzzle from stdin and print the solution to stdout. Will read until `Ctrl+D` or EOF marker. 

### Functional decomposition into modules

The Sudoku will be separated into 3 primary separate modules: _creator_, _solver_, and _sudoku_ (found in `creator.c`, `solver.c`, and `sudoku.c` all within their respective directories). The _create_ module will be tasked with creating a randomized sudoku puzzle with a unique solution, whereas the solve module will be tasked with taking that puzzle and finding the solution. Both of these modules will serve as method libraries that implement .h files. Sudoku will be the main “runner” that will parse the arguments and call the according create or solve methods as needed.

For the create module, we anticipate the following functions:
* _generate()_: which generates a random table based on the mode
* _createUniqueTable()_: which is essentially a wrapped class for generate, but includes the logic to check for unique solution
* _backtrackRand()_: runs a backtracking algorithm to fill in the board in random order
* _checkUniqueness()_: used to determine whether a generated board has a unique solution

For the solve module, we anticipate the following functions:
* _solveSudoku()_: which takes a table and initializes anything needed to solve the table
* _backtrack()_: runs a backtrack algorithm to solve the sudoku (useful for unit testing)
* _backtrackRev()_: runs a backtrack algorithm with the reverse order of numbers to solve the sudoku (useful for unit testing)
* _isSolved()_: Checks whether a sudoku board was fully solved. 


The solve module may also include a `struct validator` that effectively is a storage unit for several boolean matrices. These matricies will store information
about which rows, columns, and boxes contain which numbers. That is, if the number x is located at (i, j) in the board, then `row[i][x]=true`, `col[j][x]=true`, and `boxes[i/3][j/3][x]=true`. You can see more about this in `validator.c` and its respective header file under the solver directory. 


For the sudoku module, we anticipate the following functions:
* _main()_: parses arguments and handles them and will call other modules
* _validateParam()_: checks the arguments to make sure they're valid
* _solveTable()_: solves the sudoku table
* _createTable()_: creates a unique sudoku table

We will also include a 4th module that will just store a library of methods (`sudokuTable.c`) that will contain a `struct sudokuTable` useful to the Sudoku board. We anticipate the following methods:

* *sudokuTable_new()*: creates a `struct sudokuTable`
* *sudokuTable_set()*: sets a value in the sudoku table at a given row and column
* *sudokuTable_get()*: returns a value in the sudoku table at a given row and column
* *sudokuTable_delete()*: deletes the struct and returns memory to the computer
* *sudokuTable_print()*: which will print the table to stdout, in either of the given modes
* *sudokuTable_load()*: which will load the table from stdin, reading which mode it is and setting the struct to the same mode accordingly
* We anticipate some random getter methods for certain properties of the sudokuTable


### Dataflow through modules

* _main()_, which calls helper functions to validate the parameters, calls the either of the subsequent methods
* _createTable()_, which calls the _createUniqueTable()_ in creator and any helper methods, as well as _printTable()_ to stdout
* _solveTable()_, which will call _sudokuTable_load()_, and then _solveSudoku()_, and finally _printTable()_ to stdout on the solved table



### Pseudo code for logic/algorithmic flow

*__Solve__*
1. Initialize data structures to store which indices have numbers or spaces
2. Call backtracking method which will recurse through columns first, then iterate through rows
    1. If we have filled the whole column, then we move onto the next row
    2. If we come across an empty space, then we check all numbers which can be validly placed in the empty space, and repeat step 2 with updated board
    3. If we come across a number, then we just keep recurring through through the columns
3. Once we have reached the bottom right corner, then we have successfully recurred through all columns and iterated through all rows so we return valid sudoku board. 

*__Create__*
1. Start with a random board, and then using the backtracking algorithm solve the board in a random way. 
2. Pick a random coordinate which contains a valid number and pluck the number in that cell. 
3. Then, attempt to solve that board with the number now removed
    1. If the board is solvable and still has a unique solution, then repeat step 2. Do this until we have plucked the specified number of empty cells. 
    2. Otherwise, put the number back, and repeat step 2. 


### Major data structures

* `int**` which is a square matrix to represent the sudoku board. 
* `struct sudokuTable` to store this array, and also information about the board format and dimension. 
* `struct validator` to store necessary matrices to store information about the numbers on the board. 


### Visual Representation

Our sudoku would produce and be able to read tables built with characters such as `|` and `_`. Each major group will be separated by these symbols to show the 9 3x3 cubes that make up a sudoku board. An example of this is

```
----------------------------------
|  0  0  0 |  0  0  0 |  0  0  0 | 
|  4  0  0 |  0  0  0 |  3  0  2 | 
|  0  2  6 |  0  0  0 |  5  0  0 | 
----------------------------------
|  3  0  0 |  0  8  0 |  0  0  9 | 
|  0  7  0 |  0  0  0 |  4  0  0 | 
|  0  0  0 |  9  0  5 |  0  0  7 | 
----------------------------------
|  1  3  0 |  0  2  0 |  0  0  4 | 
|  0  0  2 |  0  1  0 |  8  0  5 | 
|  0  0  8 |  7  0  0 |  9  0  0 | 
----------------------------------
```

Otherwise, the solve mode should be able to read from the standard format, i.e. every number in the puzzle is separated by a single space and 0s are used to represent missing numbers.

### Testing plan

__Unit Testing__

We plan to unit test functions described in sudokuLib.h, alongside functions _generateTable()_ and _readTable()_ used by the create and solve modes, considering various edge cases.


__Fuzz-testing__

Using the create mode to perform automated testing by having it generate n puzzles. The testing would check if the solve program is able to produce a solution that adheres to the rules of Sudoku, without changing the non-zero values of the original board. The testing should also check if the create mode was able to generate a board that has a unique solution.

We also plan to use significant regression testing throughout our entire project to ensure the security of our code.