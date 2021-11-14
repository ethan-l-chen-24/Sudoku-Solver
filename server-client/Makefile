# Makefile for server-client
#
# David Kotz, May 2016
# Xia Zhou, August 2017
# Temi Prioleau, 2020
#
# edited for Sudoku by Ethan Chen, Bansharee Ireen, Jeffrey Jiang, November 2021

S = ../solver
C = ../creator

PROGS = client server 
LIBS = $S/solver.a $C/creator.a ../sudoku/sudokuTable.o

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$S -I$C
CC = gcc
MAKE = make

all: $(PROGS)

########### client ##################
client: client.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

########### server #################
server: server.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

.PHONY: all valgrind 

clean:
	rm -rf *~ *.o *.dSYM
	rm -f $(PROGS) 