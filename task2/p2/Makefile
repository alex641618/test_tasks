all: p2

p2: src/p2.cpp
	mkdir -p obj
	g++ -fpic -c -I./include ./src/p2.cpp -o ./obj/p2.o
	mkdir -p bin
	g++ ./obj/p2.o -lfuncs -L../lib/bin -Wl,-rpath="\$$ORIGIN/../../lib/bin" -o ./bin/p2