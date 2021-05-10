INCLUDE_FLAGS=-I./lib/cxxopts-2.2.1/include -I./lib/termcolor-2.0.0/include -I./lib/ethash-0.6.0/include
LINK_FLAGS=-lsecp256k1 -lsodium
CFLAGS= -g3 -Wall -Wextra -Wvla $(INCLUDE_FLAGS)
CC=g++
ETHASH_SRC=./lib/ethash-0.6.0/lib/keccak/keccak.c 
MEME=./lib/ethash-0.6.0/lib/keccak/keccakf800.c
OUT_PRG=minth

compile:
	$(CC) $(CFLAGS) ./src/*.cpp ./src/**/*.cpp -o $(OUT_PRG)

eth:
	mkdir -p ./build
	cc -c $(CFLAGS) $(ETHASH_SRC) -o ./build/keccak.o
	cc -c $(CFLAGS) ./src/eth/eth.c -o ./build/eth.o
	$(CC) $(CFLAGS) ./src/eth/main.cpp ./build/eth.o ./build/keccak.o $(LINK_FLAGS) -o $(OUT_PRG)



clean: 
	rm $(OUT_PRG) && rm -rf build/*
