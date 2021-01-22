.PHONY: all clean

all: dom tile addr rand

dom: dom.cpp
	g++ dom.cpp -g -o dom

tile: tile.cpp
	g++ tile.cpp -g -o tile

addr: addr.cpp
	g++ addr.cpp -g -o addr

rand: rand.cpp
	g++ rand.cpp -g -o rand

clean:
	rm -rf tile dom addr rand
