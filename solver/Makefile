# Makefile for 'common' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019
# edited for solver by Ethan Chen, Bansharee Ireen, and Jeffrey Jiang, November 2021

OBJS = solver.o validator.o
LIBS = 
LIB = solver.a
CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc

# build archive file
$(LIB): $(OBJS) $(LIBS)
	ar cr $(LIB) $(LIBS) $(OBJS) 

.PHONY: all clean sourcelist test

all: solver.a

# list all the sources and docs in this directory.
sourcelist: Makefile *.md *.c *.h
	@echo $^

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
	rm -f index
