# Makefile for 'sudoku' module
#
# Ethan Chen, Bansharee Ireen, Jeffrey Jiang, November 2021

OBJS = sudoku.o creator.o solver.o sudokuTable.o
LIBS =

# uncomment the following to turn on testing
TESTING = -DUNITTEST #-DFUZZTEST 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50.a
CC = gcc
MAKE = make

unittest: unittest.o ../creator/creator.o ../solver/solver.o ../sudoku/sudokuTable.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

fuzztester: fuzztester.o ../creator/creator.o ../solver/solver.o ../sudoku/sudokuTable.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

../creator/creator.o: ../creator/creator.h ../sudoku/sudokuTable.h ../solver/solver.h 
../solver/solver.o: ../solver/solver.h ../sudoku/sudokuTable.h 
../sudoku/sudokuTable.o: ../sudoku/sudokuTable.h ../libcs50/file.h


.PHONY: create solve test valgrind clean utest fuzz

all: fuzztester unittest 

# fuzz testing
fuzz: fuzztester
	./fuzztester 4 9

unit: unittest
	./unittest

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f core
	rm -f unittest
	rm -f fuzztester