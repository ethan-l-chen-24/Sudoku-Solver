# ETHAN CHEN, BANSHAREE IREEN, JEFFREY JIANG
# testing.sh - integration testing for sudoku module

touch ../tables/easyTable.txt
touch ../tables/hardTable.txt
touch ../tables/valgrindTable.txt


# VALID TESTS
# test 1:creating a board on easy mode
./sudoku create easy > ../tables/easyTable.txt

# test 2: creating a board on hard mode
./sudoku create hard > ../tables/hardTable.txt

# test 3: solving the board made by test 1
./sudoku solve easy < ../tables/easyTable.txt

# test 4: solving the board made by test 2
./sudoku solve hard < ../tables/easyTable.txt


# INVALID INPUTS

# invalid mode
./sudoku wrong easy

# invalid difficulty
./sudoku create wrong

# 3rd argument can only be dimension
./sudoku create easy nonIntArg

# using invalid dimension
./sudoku solve hard 10


# SOLVABILITY
# trying to solve a known unsolvable board
./sudoku solve easy < ../tables/unsolvableTable

# VALGRIND TESTS
# checking for memory leaks on create mode
valgrind --leak-check=full --show-leak-kinds=all ./sudoku create easy > ../tables/valgrindTable.txt

# checking for memory leaks on solve mode
valgrind --leak-check=full --show-leak-kinds=all ./sudoku solve easy < ../tables/valgrindTable.txt



