# C compiler
CC = g++
ICC = icc
#CC_FLAGS = -g -O3 -fopenmp
CC_FLAGS = -g -O0
#OFFLOAD_CC_FLAGS = -offload-option,mic,compiler,"-no-opt-prefetch"

all: needle

needle: 
	$(CC) $(CC_FLAGS) needle.cpp -o needle 

clean:
	rm -f needle needle_offload
