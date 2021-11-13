# Makefile for socket examples
#
# David Kotz, May 2016
# Xia Zhou, August 2017
# Temi Prioleau, 2020

S = ../solver
C = ../creator

PROGS = client server 
LIBS = $S/solver.a $C/creator.a ../sudoku/sudokuTable.o

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$S -I$C
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

all: $(PROGS)

########### client ##################
client: client.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

########### server #################
server: server.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

server.o: ../creator/creator.h ../solver/solver.h ../sudoku/sudokuTable.h

.PHONY: all valgrind 

clean:
	rm -rf *~ *.o *.dSYM
	rm -f $(PROGS) 