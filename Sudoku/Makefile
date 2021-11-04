# Makefile for 'sudoku' module
#
# Ethan Chen, Bansharee Ireen, Jeffrey Jiang, November 2021

OBJS = sudoku.o creator.o solver.o  sudokuLib.o unittest.o
LIBS =

# uncomment the following to turn on verbose memory logging
TESTING = #-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

sudoku: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

unittest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

sudoku.o: creator.h solver.h
creator.o: creator.h 
solver.o: solver.h sudokuLib.h
sudokuLib.o: sudokuLib.h
unittest.o: creator.h solver.h sudokuLib.h 

.PHONY: all run test valgrind clean utest

all: sudoku unittest

test: sudoku testing.sh
	bash -v testing.sh

# edit for args
run: sudoku
	./sudoku
	
# edit for args
valgrind: sudoku 
	$(VALGRIND) ./sudoku 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f hashtabletest
	rm -f core
	rm -f unittest
	rm -f sudoku

utest: unittest
	./unittest