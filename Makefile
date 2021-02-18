CC=g++
CFLAGS=-std=c++11 -Wall -g
EXE_NAME=hello_world

build: bin bin/main.o bin/hash_utils.o bin/sha-256.o
	$(CC) $(CFLAGS) bin/*.o -o bin/$(EXE_NAME)

bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp -o $@

bin/hash_utils.o: src/crypto/hash_utils.cpp
	$(CC) $(CFLAGS) -c src/crypto/hash_utils.cpp -o $@

bin/sha-256.o: src/crypto/sha-256.c
	gcc -c src/crypto/sha-256.c -o $@

clean: 
	rm -rf bin/*.o bin/$(EXE_NAME)

bin:
	mkdir -p $@