# DP With Friends 
## Jeffrey Jiang, Bansharee Ireen, Ethan Chen
## CS50 Fall 2021, Final Project - Sudoku 2.0

GitHub usernames: ethan-l-chen-24
                  banshee56
                  jiangj3

 ### Directory Layout
- Libcs50 directory
    - Contains the various abstract data structure files along with helper files for reading, writing, and memory mangament. 
- Tables directory
    - Contains text files which will hold various sudoku table boards.
- Testing directory
    - `fuzztester.c` generates `n` number of boards (defaulted to hard mode, but you can choose the dimension). Checks if generated board is unique, and checks if solved board is the same as generated board and is a valid solution. 
    - `testing.sh` contains test cases to demonstrate normal functionality on different levels along with catching various invalid cases. `testing.out` contains the output of `testing.sh` when specified. 
    - `unittest.c` contains various unit tests which comprehensively tests the indiviudal modules and functions. 
    - `TESTING.md` contains our comments and methodology about our testing.  
- Sudoku directory
    - `sudokuTable.c` and `sudokuTable.h` contains the modularized functions and attributes of our abstract `sudokuTable` data structure. 
    - `fuzztester.c`, `unittest.c`, `testing.sh` all contain various test cases checking the functionality of the files above. 
- Solver directory
    - `solver.c` and `solver.h` contain the backtracking algorithm for solving the board, and contains logic to check whether the board is indeed solvable. 
- Creator directory 
    - `creator.c` and `creator.h` contain the logic for generating a sudoku board and also check whether the generated boards are unqiue. 

```bash
.
├── creator
│   ├── creator.c
│   ├── creator.h
│   ├── Makefile
│   └── README.md
├── DESIGN.md
├── IMPLEMENTATION.md
├── libcs50
│   ├── file.c
│   ├── file.h
│   ├── file.md
│   ├── libcs50-given.a
│   ├── Makefile
│   └── README.md
├── Makefile
├── README.md
├── server-client
│   ├── client.c
│   ├── Makefile
│   ├── README.md
│   └── server.c
├── solver
│   ├── Makefile
│   ├── README.md
│   ├── solver.c
│   ├── solver.h
│   ├── validator.c
│   └── validator.h
├── sudoku
│   ├── Makefile
│   ├── README.md
│   ├── sudoku.c
│   ├── sudokuTable.c
│   └── sudokuTable.h
├── tables
│   ├── easy16.txt
│   ├── easyTable.txt
│   ├── hard16.txt
│   ├── hardTable.txt
│   ├── invalidTable.txt
│   ├── loadtest.txt
│   ├── table1.txt
│   ├── table2.txt
│   ├── table3.txt
│   ├── unsolvableTable.txt
│   └── valgrindTable.txt
└── testing
    ├── fuzztester.c
    ├── Makefile
    ├── README.md
    ├── TESTING.md
    ├── testing.out
    ├── testing.sh
    └── unittest.c
```

### Program Usage
1. Type `make` at the root directory. Then, navigate to the `sudoku` direcotry using `cd sudoku/`.
2. Type `./sudoku mode difficulty [dimension]` where 
- _mode_: is a string which can either be `create` or `solve`. 
- _difficulty_: is a string which can either be `easy` or `hard`
- _dimension_: is a number which can be either 4, 9 or 16 (if not specified, defaults to 9). 
Solve will read from stdin until EOF (`Ctrl+D`)


### Extra 
We decided to implement two "toppings" which were considered extra to the standard functionality of the sudoku generator and solver. 
1. Our sudoku project extends beyond the standard 9x9 to include generation and solving for 4x4 and 16x16. 
2. We also included server-client functionality so the all the solving and generation is done on a server, and the client can interact with the server with various commands. To see more information about this, see the `README.md` in the server-client directory. 

### Sources
The sources we primarily consulted were Wikipedia, Stack overflow, and the CS50 lectures and slides. However, we guarentee that we wrote all the code and did not copy it with the exception of server-client. See more about that in server-client directory in the README. 


