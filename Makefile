CXX_INCLUDE_FLAGS=-I./lib/cxxopts-2.2.1/include -I./lib/termcolor-2.0.0/include 
C_INCLUDE_FLAGS=-I./lib/ethash-0.6.0/include
LINK_FLAGS=-lsecp256k1
CFLAGS= -g3 -Wall -Wextra -Wvla $(C_INCLUDE_FLAGS)
CXXFLAGS= -g3 -Wall -Wextra -Wvla $(CXX_INCLUDE_FLAGS) $(C_INCLUDE_FLAGS)
CC=cc
CXX=g++

ETHASH_SRC=./lib/ethash-0.6.0/lib/keccak/keccak.c 
MINTH_C_SRC=./src/eth/eth.c

OBJECT_DEPS=./build/eth.o ./build/keccak.o

OUT_PRG=minth

compile: object_deps
	$(CXX) $(CXXFLAGS) ./src/*.cpp ./src/**/*.cpp $(OBJECT_DEPS) $(LINK_FLAGS) -o $(OUT_PRG)

object_deps:
	mkdir -p ./build
	$(CC) -c $(CFLAGS) $(ETHASH_SRC) -o ./build/keccak.o
	$(CC) -c $(CFLAGS) $(MINTH_C_SRC) -o ./build/eth.o

rlp_c:
	$(CC) $(CFLAGS) -I./lib/C-STL-master/include ./src/eth/rlp.c ./src/eth/vector-t.c ./src/eth/vector-uchar.c ./lib/C-STL-master/src/memory.c -o $(OUT_PRG)

rlp_h: 
	$(CC) $(CFLAGS) ./src/eth/rlp.cpp -o $(OUT_PRG)

clean: 
	rm $(OUT_PRG) && rm -rf build/*
