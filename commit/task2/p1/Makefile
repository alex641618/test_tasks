all: p1

p1: src/p1.cpp
	mkdir -p obj
	g++ -fpic -c -I./include ./src/p1.cpp -o ./obj/p1.o
	mkdir -p bin
	g++ ./obj/p1.o -lfuncs -L../lib/bin -Wl,-rpath="\$$ORIGIN/../../lib/bin" -o ./bin/p1