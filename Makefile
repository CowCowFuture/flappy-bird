CFLAGS=-Wall -pedantic -lraylib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

bird: main.c pipe.c pipe.h
	gcc -o bird ${CFLAGS} main.c pipe.c
