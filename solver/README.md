# Final Project - Jeffrey Jiang, Bansharee Ireen, Ethan Chen
## Sudoku Solver, CS50 Fall 2021

## Solver

The solver directory holds the modules to solve a given valid sudoku board. 

## Files

* `solver.c` - the module that handles the solving of sudoku boards
* `solver.h` - the header file describing the module functions
* `validator.c` - holds the modules for the validator data structure
* `validator.h` - the header file describing the respective module functions
* `Makefile` - creates the solver.a file to store the object files

## Assumptions

1. The caller only requests sudoku boards of dimensions 4, 9, or 16.

## Limitations

1. Cannot create boards of dimension greater than 16.

## Compilation

`make all` in this directory to create the archive.

`make solve` in the sudoku directory solves a board using the following command:

`./sudoku solve hard 9`
