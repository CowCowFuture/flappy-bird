CFLAGS=-Wall -pedantic -lraylib

bird: main.c pipe.c pipe.h
	gcc -o bird ${CFLAGS} main.c pipe.c
