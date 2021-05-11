CXX_INCLUDE_FLAGS=-I./lib/cxxopts-2.2.1/include -I./lib/termcolor-2.0.0/include 
C_INCLUDE_FLAGS=-I./lib/ethash-0.6.0/include
LINK_FLAGS=-lsecp256k1
CFLAGS= -g3 -Wall -Wextra -Wvla $(C_INCLUDE_FLAGS)
CXXFLAGS= -g3 -Wall -Wextra -Wvla $(CXX_INCLUDE_FLAGS) $(C_INCLUDE_FLAGS)
CC=cc
CXX=g++

ETHASH_SRC=./lib/ethash-0.6.0/lib/keccak/keccak.c 
MINTH_C_SRC=./src/eth/eth.c

OUT_PRG=minth

compile:
	$(CXX) $(CXXFLAGS) ./src/*.cpp ./src/**/*.cpp -o $(OUT_PRG)

eth:
	mkdir -p ./build
	$(CC) -c $(CFLAGS) $(ETHASH_SRC) -o ./build/keccak.o
	$(CC) -c $(CFLAGS) $(MINTH_C_SRC) -o ./build/eth.o
	$(CXX) $(CXXFLAGS) ./src/eth/main.cpp ./build/eth.o ./build/keccak.o $(LINK_FLAGS) -o $(OUT_PRG)

clean: 
	rm $(OUT_PRG) && rm -rf build/*
