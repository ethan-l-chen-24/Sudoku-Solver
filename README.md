# DP With Friends 
## Jeffrey Jiang, Bansharee Ireen, Ethan Chen
## CS50 Fall 2021, Final Project - Sudoku 2.0

GitHub usernames: ethan-l-chen-24
                  banshee56
                  jiangj3

### Libcs50 directory
- Contains the various abstract data structure files along with helper files for reading, writing, and memory mangament. 

### Tables directory
- Contains text files which will hold various sudoku table boards.

### Testing directory
- `fuzztester.c` generates `n` number of boards (defaulted to hard mode, but you can choose the dimension). Checks if generated board is unique, and checks if solved board is the same as generated board and is a valid solution. 
- `testing.sh` contains test cases to demonstrate normal functionality on different levels along with catching various invalid cases. `testing.out` contains the output of `testing.sh` when specified. 
- `unittest.c` contains various unit tests which comprehensively tests the indiviudal modules and functions. 
- `TESTING.md` contains our comments and methodology about our testing. 

### Sudoku directory
- `sudokuTable.c` and `sudokuTable.h` contains the modularized functions and attributes of our abstract `sudokuTable` data structure. 
- `fuzztester.c`, `unittest.c`, `testing.sh` all contain various test cases checking the functionality of the files above. 

### Solver directory
- `solver.c` and `solver.h` contain the backtracking algorithm for solving the board, and contains logic to check whether the board is indeed solvable. 

### Creator directory 
- `creator.c` and `creator.h` contain the logic for generating a sudoku board and also check whether the generated boards are unqiue. 

