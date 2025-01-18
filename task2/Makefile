all: lib p1 p2

lib:
	cd ./lib/ && make

p1: lib
	cd ./p1/ && make

p2: lib
	cd ./p2/ && make

clean:
	rm -rf ./lib/obj ./lib/bin ./p1/obj ./p1/bin ./p2/obj ./p2/bin

.PHONY: lib p1 p2