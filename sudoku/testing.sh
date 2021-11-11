# ETHAN CHEN, BANSHAREE IREEN, JEFFREY JIANG
# testing.sh - integration testing for sudoku module

touch ../tables/easyTable.txt
touch ../tables/hardTable.txt
touch ../tables/valgrindTable.txt


# VALID TESTS
./sudoku create easy > ../tables/easyTable.txt

./sudoku create hard > ../tables/hardTable.txt

./sudoku solve easy < ../tables/easyTable.txt

./sudoku solve hard < ../tables/easyTable.txt


# INVALID INPUTS
./sudoku wrong easy

./sudoku create wrong

./sudoku create easy tooManyArgs


# SOLVABILITY
./sudoku solve easy < ../tables/unsolvableTable

# VALGRIND TESTS
valgrind --leak-check=full --show-leak-kinds=all ./sudoku create easy > ../tables/valgrindTable.txt

valgrind --leak-check=full --show-leak-kinds=all ./sudoku solve easy < ../tables/valgrindTable.txt



