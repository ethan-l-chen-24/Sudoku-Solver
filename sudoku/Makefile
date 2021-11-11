# Makefile for 'sudoku' module
#
# Ethan Chen, Bansharee Ireen, Jeffrey Jiang, November 2021

OBJS = sudoku.o creator.o solver.o sudokuTable.o
LIBS =

# uncomment the following to turn on testing
TESTING = #-DUNITTEST #-DFUZZTEST 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50.a
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

sudoku: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

unittest: unittest.o creator.o solver.o sudokuTable.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

fuzztester: fuzztester.o creator.o solver.o sudokuTable.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

sudoku.o: creator.h solver.h sudokuTable.h
creator.o: creator.h sudokuTable.h solver.h 
solver.o: solver.h sudokuTable.h 
sudokuTable.o: sudokuTable.h ../libcs50/file.h
unittest.o: creator.h solver.h sudokuTable.h
fuzztester.o: creator.h solver.h sudokuTable.h

.PHONY: create solve test valgrind clean utest fuzz

all: sudoku 

# testing script
test: sudoku testing.sh
	bash -v testing.sh &> testing.out

# create mode
create: sudoku
	./sudoku create hard > ../tables/table1.txt
	
# solve mode
solve: sudoku
	./sudoku solve hard < ../tables/table1.txt 

# fuzz testing
fuzz: fuzztester
	./fuzztester 4 16
	
# edit for args
valgrind: sudoku 
	$(VALGRIND) ./sudoku create easy > ../tables/table1.txt
	$(VALGRIND) ./sudoku solve easy < ../tables/table1.txt 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f hashtabletest
	rm -f core
	rm -f unittest
	rm -f fuzztester
	rm -f sudoku

utest: unittest
	./unittest