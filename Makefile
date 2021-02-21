CC=g++
CFLAGS=-std=c++17 -Wall -g -Isrc/crypto/
EXE_NAME=hello_world

build: bin bin/main.o bin/sha256.o bin/block.o
	$(CC) $(CFLAGS) bin/*.o -o bin/$(EXE_NAME)

bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp -o $@

bin/block.o: src/blockchain/block.cpp
	$(CC) $(CFLAGS) -c src/blockchain/block.cpp -o $@

bin/sha256.o: src/crypto/SHA256.cpp src/crypto/SHA256.h
	$(CC) $(CFLAGS) -c src/crypto/SHA256.cpp -o $@

clean: 
	rm -rf bin/*.o bin/$(EXE_NAME)

bin:
	mkdir -p $@