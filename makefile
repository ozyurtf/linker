CFLAGS=-g 
CXXFLAGS=-std=c++11
CC=g++

linker: linker.cpp
	$(CC) $(CXXFLAGS) linker.cpp -o linker

clean:
	rm -f linker *~

check_version:
	$(CC) --version
