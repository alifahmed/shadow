.PHONY: all clean cleanall

SRC_FILES = $(shell find . -type f -name '*.cpp')
OBJ_FILES = $(patsubst %.cpp, %.out, $(SRC_FILES))

all: $(OBJ_FILES)

	
%.out : %.cpp
	g++ $^ -o $@ -mavx -O0 -g


clean:
	rm -rf $(OBJ_FILES)
	
cleanall: clean
	rm -rf $(SRC_FILES)
