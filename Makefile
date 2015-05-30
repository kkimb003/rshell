CXX = g++
CFLAGS = -ansi -pedantic -Wall -Werror
VPATH = src
FILEPATH = ./src/main.cpp
OUTPATH = ./bin/rshell
FILEPATHCP = ./src/cp.cpp
OUTPATHCP = ./bin/cp
objects = main.o

all: 
	mkdir -p ./bin
		$(CXX) $(CFLAGS) $(FILEPATH) -o $(OUTPATH)

rshell: 
	mkdir -p ./bin

	$(CXX) $(CFLAGS) $(FILEPATH) -o $(OUTPATH) 

cp: 
	if [ ! -d bin ]; then mkdir bin; fi
	g++ $(CFLAGS) src/cp.cpp -o bin/cp


clean:
		rm -rf ./bin
