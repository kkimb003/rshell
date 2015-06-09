CXX = g++
CZZ = g++ -std=c++11
CFLAGS = -ansi -pedantic -Wall -Werror
VPATH = src
FILEPATH = ./src/main.cpp
FILEPATHLS = ./src/ls.cpp
OUTPATH = ./bin/rshell
OUTPATHLS = ./bin/ls
FILEPATHCP = ./src/cp.cpp
OUTPATHCP = ./bin/cp
objects = main.o

all: 
	mkdir -p ./bin
		$(CXX) $(CFLAGS) $(FILEPATH) -o $(OUTPATH)
		$(CXX) $(CFLAGS) $(FILEPATHLS) -o $(OUTPATHLS) 
rshell: 
	mkdir -p ./bin

	$(CXX) $(CFLAGS) $(FILEPATH) -o $(OUTPATH) 

cp: 
	if [ ! -d bin ]; then mkdir bin; fi
	g++ $(CFLAGS) src/cp.cpp -o bin/cp
ls:
	mkdir -p ./bin

	$(CXX) $(CFLAGS) $(FILEPATHLS) -o $(OUTPATHLS) 

clean:
		rm -rf ./bin
