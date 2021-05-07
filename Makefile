INCLUDE_FLAGS=-I./lib/cxxopts-2.2.1/include -I./lib/termcolor-2.0.0/include
CFLAGS= -g3 -Wall -Wextra -Wvla $(INCLUDE_FLAGS)
CC=g++
OUT_PRG=ethwall

compile:
	$(CC) $(CFLAGS) ./src/*.cpp ./src/**/*.cpp -o $(OUT_PRG)

clean: 
	rm $(OUT_PRG)
