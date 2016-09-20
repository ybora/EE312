
SHELL:=/bin/bash
CC:=g++

llex: llex.c
	$(CC) --std=c++11 -g -o llex llex.c 

leakcheck: llex
	valgrind --leak-check=yes ./llex

clean: 
	/bin/rm llex

renew: 
	touch llex.c

