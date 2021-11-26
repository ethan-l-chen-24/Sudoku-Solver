# Testing Sudoku

## Files

### `testing.sh`

The bash script containing the test cases. This includes valid tests, invalid input tests, and tests on valid edge cases. The final three tests check for memory leaks using `valgrind`.

It includes valid tests that create sudoku boards with unique solutions and then solve those boards while adhering to the rules of sudoku.

It also runs test cases with invalid inputs for the three arguments accepted by `sudoku.c`.

### `testing.out`

Result of running the tests in `testing.sh`.

### `unittest.c`

Runs smaller unit tests on certain key functions used by the program.

### `fuzztester.c`

Creates `n` number of boards on `hard` difficulty at a chosen `dimenion` with `n` and `dimension` accepted as arguments.

### `Makefile`

Contains targets for `unittest`, `fuzztester`, and `valgrind`. The `valgrind` test runs memory checks on every test called by `unittest` and `fuzztester`.

It runs the following commands:

`unittest` - `./unittest`

`fuzzteser` - `./fuzztester 4 9`

`valgrind` -

```makefile
$(VALGRIND) ./fuzztester 4 9
$(VALGRIND) ./unittest
```

## Usage

### `unittest`

`make unit` in the testing directory runs `unittest.c`. This can also be acheived using the following command:

`./unittest`

### `fuzztester`

`make fuzz` in the testing directory runs `fuzztester.c` with the following default arguments:

`./fuzztester 4 9`

This can be done with different arguments using the following command:

`./fuzztester n dimension`

where,

* n is the number of boards to create
* dimension is the dimension for each of the n boards

### Integration Testing

`make test` in the the testing directory runs the `testing.sh` bash script. Otherwise run `bash -v testing.sh >& testing.out` in the command-line.

Tests 1-10 are valid tests that create and solve boards of various dimensions on both levels of difficulty.

Tests 11-17 are invalid tests:
11-14 uses invalid inputs
Test 15 uses an incorrect format for a table
Test 16 uses an extra argument
Test 17 attempts to solve a board that does not follow the rules of Sudoku

Tests 18-20 run valgrind tests on creating an easy board, solving the board, and then attempting to solve the table from test 15.

## Unit Testing

Simply `make unit` in the `common` directory to run unit testing.

### `test_new`

Tests `sudokuTable_new` by creating a new board and selectively filling cells.

### `test_create`

Tests `createUniqueTable` to create a valid 9x9 board on `hard` mode.

### `test_load`

Tests `sudokuTable_load` to create a 9x9 sudoku bord on `hard` mode, printing it to a file and then loading it from the file. It checks if the 2 `sudokuTable_t` structs are identical.

### `test_uniqueness`

Tests if the solving program solves 2 identical boards with the same unique solution.

## Fuzztester

Runs `n` boards of dimension `d` on `hard` mode, performing the following:

* For the created board, checking for uniqueness
* For the solved board, whether the solved board follows the rules of Sudoku or not

`changedNum`

Checks if any of the starting numbers on the original board were changed by the `solver` program.

`isRepeat`

Checks if the solved board repeats a particular number on the row, column, or the box it is placed in.

### Timed Runs

Generate Easy: 0.008s, 0.010s, 0.011s, 0.007s, 0.009s
Avg: 0.009s

Generate Hard: 0.171s, 0.015s, 0.025s, 0.173s, 0.672s
Avg: 0.221s

Solve Easy: 0.003s, 0.003s, 0.001s, 0.002s, 0.004s
Avg: 0.002s

Solve Hard: 0.005s, 0.011s, 0.003s, 0.003s, 0.005s
Avg: 0.005s
