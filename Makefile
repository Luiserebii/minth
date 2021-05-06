INCLUDE_FLAGS=-I./lib/cxxopts-2.2.1/include
CFLAGS= -g3 -Wall -Wextra -Wvla $(INCLUDE_FLAGS)
CC=g++

compile:
	$(CC) $(CFLAGS) ./src/*.cpp -o ethwall

clean: 
	rm a.out
