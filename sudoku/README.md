# Final Project - Jeffrey Jiang, Bansharee Ireen, Ethan Chen
## Sudoku Solver Sudoku Module, CS50 Fall 2021

### sudoku module

This is a module that handles the executable version of the sudoku project according to the design specs, and holds the code for the `struct sudokuTable` which is used in various modules. The module includes files `sudoku.c`, `sudokuTable.c`, and `sudokuTable.h`

### Files

* `sudoku.c` - an executable version to create and solve sudoku tables on the command line
* `sudokuTable.c` - code for a struct that stores the sudoku table, as well as methods to manipulate and use it
* `sudokuTable.h` - the header file for `sudokuTable.c`
* `Makefile` - compiles the files

### sudoku

As described in `../DESIGN.md`, this module can be run using `./sudoku mode difficulty [dimension]`. The _mode_ can be either `create` or `solve`, while the _difficulty_ can be either `easy` or `hard`, where the _difficulty_ does not matter while in solve mode. Additionally, the module can handle _dimensions_ of `4`, `9`, or `16`, with the default being `9` if no dimension value is given.

### sudokuTable

The `struct sudokuTable` is constructed in this module, as well as any necessary methods. This struct is imported into several other modules in the project, such as `creator` and `solver`

### Assumptions

1. The inputted sudoku table does not contain any negative numbers
2. 4, 9, or 16 are selected as the dimensions

### Compilation

To compile, just call `make`. This will compile the sudoku file and create the `./sudoku` executable.