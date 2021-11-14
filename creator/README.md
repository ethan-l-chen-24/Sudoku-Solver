# Final Project - Jeffrey Jiang, Bansharee Ireen, Ethan Chen
## Sudoku Creator, CS50 Fall 2021

## Creator

The creator directory holds all the modules used by the create mode of our Sudoku program.

## Files

* `creator.c` - the module that handles the creation of sudoku boards
* `creator.h` - the header file describing the module functions
* `Makefile` - creates the creator.a file to store the object files

## Assumptions

1. The caller only requests sudoku boards of dimensions 4, 9, or 16.

## Limitations

1. Cannot create boards of dimension greater than 16.

## Compilation

`make all` in this directory to create the archive.

`make create` in the sudoku directory creates a board using the following command:

`./sudoku create hard 9 > ../tables/table1.txt`
