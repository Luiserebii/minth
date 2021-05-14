CXX_INCLUDE_FLAGS=-I../lib/cxxopts-2.2.1/include -I../lib/termcolor-2.0.0/include -I./lib/Catch2-2.13.6/include
C_INCLUDE_FLAGS=-I../lib/ethash-0.6.0/include -I../lib/C-STL-master/include
LINK_FLAGS=-lsecp256k1 -lm
CFLAGS= -g3 -Wall -Wextra -Wvla $(C_INCLUDE_FLAGS)
CXXFLAGS= -g3 -Wall -Wextra -Wvla $(CXX_INCLUDE_FLAGS) $(C_INCLUDE_FLAGS)
CC=cc
CXX=g++

ETHASH_SRC=../lib/ethash-0.6.0/lib/keccak/keccak.c 
MINTH_C_SRC=../src/eth/eth.c 
CSTL_SRC=../lib/C-STL-master/src/memory.c 

OBJECT_DEPS=./build/eth.o ./build/keccak.o ./build/memory.o ./build/rlp.o ./build/vector-rlp-t.o ./build/vector-uchar.o

OUT_PRG=test

test: compile
	./$(OUT_PRG)

compile: object_deps
	$(CXX) $(CXXFLAGS) $(C_INCLUDE_FLAGS) ./src/*.cpp ../src/**/*.cpp $(OBJECT_DEPS) $(LINK_FLAGS) -o $(OUT_PRG)

object_deps:
	mkdir -p ./build
	$(CC) -c $(CFLAGS) $(ETHASH_SRC) -o ./build/keccak.o
	$(CC) -c $(CFLAGS) $(MINTH_C_SRC) -o ./build/eth.o
	$(CC) -c $(CFLAGS) $(CSTL_SRC) -o ./build/memory.o
	$(CC) -c $(CFLAGS) ../src/eth/rlp.c -o ./build/rlp.o
	$(CC) -c $(CFLAGS) ../src/eth/vector-rlp-t.c -o ./build/vector-rlp-t.o
	$(CC) -c $(CFLAGS) ../src/eth/vector-uchar.c -o ./build/vector-uchar.o

clean: 
	rm $(OUT_PRG)
