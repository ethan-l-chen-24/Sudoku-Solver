# Makefile for CS50 Tiny Search Engine
#
# David Kotz - April 2016, 2017

MAKE = make
.PHONY: all valgrind clean

############## default: make all libs and programs ##########
all: 
	$(MAKE) -C libcs50
	$(MAKE) -C sudoku

############## valgrind all programs ##########
valgrind: all
	$(MAKE) -C crawler valgrind
	$(MAKE) -C sudoku valgrind

############### TAGS for emacs users ##########
TAGS:  Makefile */Makefile */*.c */*.h */*.md */*.sh
	etags $^

############## clean  ##########
clean:
	rm -f *~
	rm -f TAGS
	$(MAKE) -C libcs50 clean
	$(MAKE) -C sudoku clean