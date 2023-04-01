CFLAGS=-Wall -lraylib
INCLUDE=-I .

bird: main.c
	gcc -o bird ${INCLUDE} ${CFLAGS} main.c
