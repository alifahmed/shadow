# C compiler
CC = g++
ICC = icc
#CC_FLAGS = -g -fopenmp -O2
CC_FLAGS = -g -O0

all: bfs

bfs: bfs.cpp 
	$(CC) $(CC_FLAGS) bfs.cpp -o bfs

clean:
	rm -f bfs bfs_offload result.txt


