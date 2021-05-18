CXX_INCLUDE_FLAGS=-I./lib/cxxopts-2.2.1/include -I./lib/termcolor-2.0.0/include -I./lib/aether/build/include
LINK_FLAGS=-lsecp256k1 -lm -laether -L./lib/aether
CXXFLAGS= -g3 -Wall -Wextra -Wvla $(CXX_INCLUDE_FLAGS) $(C_INCLUDE_FLAGS)
CXX=g++

OUT_PRG=minth

compile: aetherlib
	$(CXX) $(CXXFLAGS) ./src/*.cpp ./src/**/*.cpp $(LINK_FLAGS) -o $(OUT_PRG)

run: 
	LD_LIBRARY_PATH=./lib/aether ./minth

aetherlib:
	cd ./lib/aether && make

clean: 
	rm $(OUT_PRG) && rm -rf build/*
