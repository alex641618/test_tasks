all: libfuncs

libfuncs: funcs
	mkdir -p bin
	g++ -shared ./obj/funcs.o ./src/funcs.h -o ./bin/libfuncs.so

funcs: src/funcs.cpp
	mkdir -p obj
	g++ -fpic -c ./src/funcs.cpp -o ./obj/funcs.o

.PHONY: libfuncs funcs