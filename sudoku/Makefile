# Makefile for 'sudoku' module
#
# Ethan Chen, Bansharee Ireen, Jeffrey Jiang, November 2021

OBJS = sudoku.o creator.o solver.o  sudokuTable.o unittest.o
LIBS =

# uncomment the following to turn on verbose memory logging
TESTING = #-DUNITTEST #-DMEMTEST

#CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50.a
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

sudoku: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

unittest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

sudoku.o: creator.h solver.h sudokuTable.h
creator.o: creator.h sudokuTable.h solver.h 
solver.o: solver.h sudokuTable.h 
sudokuTable.o: sudokuTable.h ../libcs50/file.h
unittest.o: creator.h solver.h sudokuTable.h

.PHONY: all create solve test valgrind clean utest

all: sudoku unittest

test: sudoku testing.sh
	bash -v testing.sh

# edit for args
create: sudoku
	./sudoku create hard > ../tables/table1.txt
	
solve: sudoku
	./sudoku solve hard < ../tables/table1.txt 
	
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
	rm -f sudoku

utest: unittest
	./unittest