CFLAGS=-Wall -lraylib
INCLUDE=-I .

bird: main.c pipes.h
	gcc -o bird ${INCLUDE} ${CFLAGS} main.c
