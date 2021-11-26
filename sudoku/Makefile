# Makefile for 'sudoku' module
#
# Ethan Chen, Bansharee Ireen, Jeffrey Jiang, November 2021

L = ../libcs50
S = ../solver
C = ../creator

OBJS = sudoku.o sudokuTable.o
LIBS = $L/libcs50.a $S/solver.a $C/creator.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$S -I$C
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

sudoku: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

.PHONY: all create solve valgrind clean

all: sudoku sudokuTable.a

# create mode
create: sudoku
	./sudoku create hard > ../tables/table1.txt
	
# solve mode
solve: sudoku
	./sudoku solve hard < ../tables/table1.txt 

# valgrind
valgrind: sudoku
	$(VALGRIND) ./sudoku create hard > ../tables/valgrindTable.txt
	$(VALGRIND) ./sudoku solve hard < ../tables/valgrindTable.txt

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f core
	rm -f sudoku