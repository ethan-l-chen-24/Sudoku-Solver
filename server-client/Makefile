# Makefile for socket examples
#
# David Kotz, May 2016
# Xia Zhou, August 2017
# Temi Prioleau, 2020

PROGS = client server 
LLIBS = ../creator/creator.o ../solver/solver.o ../sudoku/sudokuTable.o data.o

FLAGS = # 
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

all: $(PROGS)

########### client ##################
client: client.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

server.o: ../creator/creator.h ../solver/solver.h ../sudoku/sudokuTable.h data.h

../creator/creator.o: ../creator/creator.h ../sudoku/sudokuTable.h ../solver/solver.h 
../solver/solver.o: ../solver/solver.h ../sudoku/sudokuTable.h 
../sudoku/sudokuTable.o: ../sudoku/sudokuTable.h ../libcs50/file.h

########### server #################
server: server.o $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

server.o: ../creator/creator.h ../solver/solver.h ../sudoku/sudokuTable.h data.h

clean:
	rm -rf *~ *.o *.dSYM
	rm -f $(PROGS) 