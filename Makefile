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
<<<<<<< HEAD

=======
	$(CXX) $(CFLAGS) $(FILEPATH) -o $(OUTPATH) 

cp: 
	if [ ! -d bin ]; then mkdir bin; fi
	g++ $(CFLAGS) src/cp.cpp -o bin/cp
>>>>>>> 9354c8b5f214ded26e535bd58c6a30b68344c0a4

clean:
		rm -rf ./bin
