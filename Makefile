CC=g++
CFLAGS=-std=c++11 -Wall -g
EXE_NAME=hello_world

build: bin bin/main.o
	$(CC) $(CFLAGS) bin/*.o -o bin/$(EXE_NAME)

bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp -o $@

clean: 
	rm -rf bin/*.o bin/$(EXE_NAME)

bin:
	mkdir -p $@