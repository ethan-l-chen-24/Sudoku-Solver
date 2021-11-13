# Makefile for 'sudoku' module
#
# Ethan Chen, Bansharee Ireen, Jeffrey Jiang, November 2021

S = ../solver
C = ../creator
T = ../sudoku

LIBS = $S/solver.a $C/creator.a 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$S -I$C
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

unittest: unittest.o ../sudoku/sudokuTable.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

fuzztester: fuzztester.o ../sudoku/sudokuTable.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

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