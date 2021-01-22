.PHONY: all clean

all: seq ordered prob

ordered: ordered.cpp
	g++ ordered.cpp -g -o ordered

seq: seq.cpp
	g++ seq.cpp -g -o seq

prob: prob.cpp
	g++ prob.cpp -g -o prob


clean:
	rm -rf seq ordered prob
