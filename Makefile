CFLAGS=-Wall -lraylib
INCLUDE=-I .

bird: main.c pipe.c pipe.h
	gcc -o bird ${INCLUDE} ${CFLAGS} main.c pipe.c
