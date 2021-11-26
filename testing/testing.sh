# ETHAN CHEN, BANSHAREE IREEN, JEFFREY JIANG
# testing.sh - integration testing for sudoku module

touch ../tables/easyTable.txt
touch ../tables/hardTable.txt
touch ../tables/valgrindTable.txt
touch ../tables/easy16.txt
touch ../tables/hard16.txt
touch ../tables/hard4.txt

# VALID TESTS
# test 1: creating 9x9 board on easy mode
../sudoku/sudoku create easy > ../tables/easyTable.txt

# test 2: creating 9x9 board on hard mode
../sudoku/sudoku create hard > ../tables/hardTable.txt

# test 3: solving the board made by test 1
../sudoku/sudoku solve easy < ../tables/easyTable.txt

# test 4: solving the board made by test 2
../sudoku/sudoku solve hard < ../tables/easyTable.txt

# test 5: creating 16x16 on easy board 
../sudoku/sudoku create easy 16 > ../tables/easy16.txt

# test 6: creating 16x16 board on hard mode
../sudoku/sudoku create hard 16 > ../tables/hard16.txt

# test 7: solving the board made by test 5
../sudoku/sudoku solve easy 16 < ../tables/easy16.txt

# test 8: solving the board made by test 6
../sudoku/sudoku solve hard 16 < ../tables/hard16.txt

# test 9: creating 4x4 board on hard mode
../sudoku/sudoku create hard 4 > ../tables/hard4.txt

# test 10: solving the board made by test 9
../sudoku/sudoku solve hard 4 < ../tables/hard4.txt

# INVALID INPUTS

# test 11: invalid mode
../sudoku/sudoku wrong easy

# test 12: invalid difficulty
../sudoku/sudoku create wrong

# test 13: 3rd argument can only be dimension
../sudoku/sudoku create easy nonIntArg

# test 14: using invalid dimension
../sudoku/sudoku solve hard 10 

# test 15: using invalid board
../sudoku/sudoku solve easy < ../tables/invalidTable.txt

# test 16: too many arguments
../sudoku/sudoku create easy 9 extraArg

# test 17: trying to solve a known invalid board
../sudoku/sudoku solve easy < ../tables/unsolvableTable.txt

# VALGRIND TESTS
# test 18: checking for memory leaks on create mode
valgrind --leak-check=full --show-leak-kinds=all ../sudoku/sudoku create easy > ../tables/valgrindTable.txt


# test 19: checking for memory leaks on solve mode
valgrind --leak-check=full --show-leak-kinds=all ../sudoku/sudoku solve easy < ../tables/valgrindTable.txt


# test 20: checking for memory leaks on necessary edge cases
valgrind --leak-check=full --show-leak-kinds=all ../sudoku/sudoku solve easy < ../tables/invalidTable.txt


exit 0