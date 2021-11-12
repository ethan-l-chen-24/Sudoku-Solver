# Final Project - Jeffrey Jiang, Bansharee Ireen, Ethan Chen
## Sudoku Solver, CS50 Fall 20221

### User interface

```text
./sudoku mode difficulty
```

For example: 

```text
./sudoku create hard
./sudoku solve hard
```

### Inputs and outputs

Input: 
- _mode_: is a string which can either be `create` or `solve`. 
- _difficulty_: is a string which can either be `easy` or `hard`

Output: 
If the _mode_ is set to create, then it will print to stdout a randomized sudoku puzzle with either: 
- 37 given numbers and 44 missing numbers if mode is `easy`
- 25 given numbers and 56 missing numbers if mode is `hard`

If the _mode_ is set to solve, then it will read in a valid sudoku puzzle from stdin and print the solution to stdout. 

### Functional decomposition into modules

The Sudoku will be separated into 3 separate modules: _create_, _solve_, and _sudoku_ (found in `creator.c`, `solver.c`, and `sudoku.c`). The _create_ module will be tasked with creating a randomized sudoku puzzle with a unique solution, whereas the solve module will be tasked with taking that puzzle and finding the solution. Both of these modules will serve as method libraries that implement .h files. Sudoku will be the main “runner” that will parse the arguments and call the according create or solve methods as needed.

For the create module, we anticipate the following functions:
* _generateTable()_: which generates a random table based on the mode

For the solve module, we anticipate the following functions:
* _solveSudoku()_: which takes a table and initializes anything needed to solve the table
* _backtrack()_: runs a backtrack algorithm to solve the sudoku (useful for unit testing)
* _backtrackRev()_: runs a backtrack algorithm with the reverse order of numbers to solve the sudoku (useful for unit testing)
* _checkUniqueness()_: wrapper class to call backtrack() and 

The solve module may also include a `struct validator` that effectively is a storage unit for several boolean matrices.

For the sudoku module, we anticipate the following functions:
* _main()_: parses arguments and handles them
* _createTable()_: creates the table
* _solveTable()_: solves the sudoku table
* _topping()_: provides the extra credit option

We will also include a 4th module that will just store a library of methods (`sudokuTable.c`) that will contain a `struct sudokuTable` useful to the Sudoku board. We anticipate the following methods:

* *sudokuTable_new()*: creates a `struct sudokuTable`
* *sudokuTable_set()*: sets a value in the sudoku table at a given row and column
* *sudokuTable_get()*: returns a value in the sudoku table at a given row and column
* *sudokuTable_delete()*: deletes the struct and returns memory to the computer
* *sudokuTable_print()*: which will print the table to stdout, in either of the given modes
* *sudokuTable_load()*: which will load the table from stdin, reading which mode it is and setting the struct to the same mode accordingly
* We anticipate some random getter methods for certain properties of the sudokuTable


### Dataflow through modules

* _main()_, which parses command line arguments
* _createTable()_, which calls the _generateStartTable()_ and any helper methods, as well as _printTable()_ to stdout
* _solveTable()_, which will call _readTable()_, and then _findSolution()_, and finaly _printTable()_ to stdout on the solved table
* _topping()_, which may do any of these depending on what we choose to implement


### Pseudo code for logic/algorithmic flow

*__Solve__*
1. Initialize data structures to store which indices have numbers or spaces
2. Call backtracking method which will recurse through columns first, then iterate through rows
    1. If we have filled the whole column, then we move onto the next row
    2. If we come across an empty space, then we check all numbers which can be validly placed in the empty space, and repeat step 2 with updated board
    3. If we come across a number, then we just keep recurring through through the columns
3. Once we have reached the bottom right corner, then we have successfully recurred through all columns and iterated through all rows so we return valid sudoku board. 

*__Create__ (Tentative)*
1. Randomly place in the desired number of cells into the table as long as they are valid and able to placed in that position
2. try to solve the board in forwards order (1-9) and backwards order (9-1)
3. if the boards have all of the same cells and is solvable
    1. return the board


### Major data structures

* `int**` for each row and each column which will contain which numbers are in the row or column
* `struct sudokuTable` to store this array
* `struct validator` to store necessary matrices for the efficiency of the solver


### Visual Representation

Our sudoku would produce and be able to read tables built with characters such as `|` and `_`.

Otherwise, the solve mode should be able to read from the standard format, i.e. every number in the puzzle is separated by a single space and 0s are used to represent missing numbers.

### Testing plan

__Unit Testing__

We plan to unit test functions described in sudokuLib.h, alongside functions _generateTable()_ and _readTable()_ used by the create and solve modes, considering various edge cases.


__Fuzz-testing__

Using the create mode to perform automated testing by having it generate n puzzles. The testing would check if the solve program is able to produce a solution that adheres to the rules of Sudoku, without changing the non-zero values of the original board. The testing should also check if the create mode was able to generate a board that has a unique solution.

We also plan to use significant regression testing throughout our entire project to ensure the security of our code.