# A simple makefile for CSE 100 P1

#use g++ for everything
CC= g++  	

# include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -g -Wall -std=c++11

#include debugging symbols in executable
LDFLAGS= -g	
all: bst main

bst: test_BST.o 
	g++ -o bst test_BST.o

main: main.o
	g++ -o main main.o

main.o: BST.hpp BSTNode.hpp BSTIterator.hpp 

test_BST.o: BST.hpp BSTNode.hpp BSTIterator.hpp 

clean:
	$(RM) main bst *.o
