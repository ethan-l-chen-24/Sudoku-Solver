# Makefile for 'sudoku' module
#
# Ethan Chen, Bansharee Ireen, Jeffrey Jiang, November 2021

OBJS = sudoku.o ../creator/creator.o ../solver/solver.o sudokuTable.o
LIBS =

# uncomment the following to turn on testing
TESTING = #-DFUZZTEST #-DUNITTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50.a
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

sudoku: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lm

sudoku.o: ../creator/creator.h ../solver/solver.h sudokuTable.h
../creator/creator.o: ../creator/creator.h sudokuTable.h ../solver/solver.h 
..solver/solver.o: ../solver/solver.h sudokuTable.h 
sudokuTable.o: sudokuTable.h ../libcs50/file.h

.PHONY: create solve clean

all: sudoku 

# create mode
create: sudoku
	./sudoku create hard > ../tables/table1.txt
	
# solve mode
solve: sudoku
	./sudoku solve hard < ../tables/table1.txt 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f core
	rm -f sudoku