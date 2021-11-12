# Makefile for 'sudoku' module
#
# Ethan Chen, Bansharee Ireen, Jeffrey Jiang, November 2021

OBJS = sudoku.o creator.o solver.o sudokuTable.o
LIBS =

# uncomment the following to turn on testing
TESTING = 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50.a
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

unittest: unittest.o ../creator/creator.o ../solver/solver.o ../sudoku/sudokuTable.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

fuzztester: fuzztester.o ../creator/creator.o ../solver/solver.o ../sudoku/sudokuTable.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

../creator/creator.o: ../creator/creator.h ../sudoku/sudokuTable.h ../solver/solver.h 
../solver/solver.o: ../solver/solver.h ../sudoku/sudokuTable.h 
../sudoku/sudokuTable.o: ../sudoku/sudokuTable.h ../libcs50/file.h
../sudoku/sudoku.o: ../creator/creator.h ../solver/solver.h ../sudoku/sudokuTable.h

.PHONY: valgrind clean unit fuzz

all: fuzztester unittest

# fuzz testing
fuzz: fuzztester
	./fuzztester 4 9

unit: unittest
	./unittest

test: ../sudoku/sudoku testing.sh
	bash -v testing.sh >& testing.out

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f core
	rm -f unittest
	rm -f fuzztester

valgrind: fuzztester unittest
	$(VALGRIND) ./fuzztester 4 9
	$(VALGRIND) ./unittest