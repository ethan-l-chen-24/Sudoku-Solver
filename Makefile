# Makefile for CS50 Tiny Search Engine
#
# David Kotz - April 2016, 2017

MAKE = make
.PHONY: all valgrind clean

############## default: make all libs and programs ##########
all: 
	$(MAKE) -C libcs50
	$(MAKE) -C solver
	$(MAKE) -C creator
	$(MAKE) -C sudoku
	$(MAKE) -C testing
	$(MAKE) -C server-client

############## valgrind all programs ##########
valgrind: all
	$(MAKE) -C sudoku valgrind
	$(MAKE) -C testing valgrind

############### TAGS for emacs users ##########
TAGS:  Makefile */Makefile */*.c */*.h */*.md */*.sh
	etags $^

############## clean  ##########
clean:
	rm -f *~
	rm -f TAGS
	$(MAKE) -C libcs50 clean
	$(MAKE) -C solver clean
	$(MAKE) -C creator clean
	$(MAKE) -C sudoku clean
	$(MAKE) -C testing clean
	$(MAKE) -C server-client clean