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

### Sudoku directory
- `solver.c` and `solver.h` contain the backtracking algorithm for solving the board, and contains logic to check whether the board is indeed solvable. 
- `creator.c` and `creator.h` contain the logic for generating a sudoku board and also check whether the generated boards are unqiue. 
- `sudokuTable.c` and `sudokuTable.h` contains the modularized functions and attributes of our abstract `sudokuTable` data structure. 
- `fuzztester.c`, `unittest.c`, `testing.sh` all contain various test cases checking the functionality of the files above. 


