LOCAL_CC = gcc -g -O0 -Wall
CC = gcc
#CFLAGS = -lm -fopenmp -Wall
CFLAGS = -lm -Wall


all : nn

clean :
	rm -rf *.o nn

nn : nn_openmp.c
	$(CC) -o $@ $< $(LDFLAGS) $(CFLAGS) 

hurricane_gen : hurricane_gen.c
	$(LOCAL_CC) -o $@ $< -lm

