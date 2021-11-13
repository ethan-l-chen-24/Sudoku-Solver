# Makefile for 'creator' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019
# edited for creator by Ethan Chen, Bansharee Ireen, and Jeffrey Jiang, November 2021

S = ../solver

OBJS = creator.o
LIBS = $S/solver.a
LIB = creator.a
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$S
CC = gcc

# build archive file
$(LIB): $(OBJS) $(LIBS)
	ar cr $(LIB) $(LIBS) $(OBJS) 

.PHONY: all clean sourcelist test

all: creator.a

# list all the sources and docs in this directory.
sourcelist: Makefile *.md *.c *.h
	@echo $^

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
	rm -f index
