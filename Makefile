CFLAGS=-Wall -lraylib

bird: main.c
	gcc -o bird ${CFLAGS} main.c
