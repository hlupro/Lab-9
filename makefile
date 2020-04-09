CXXFLAGS=-g -std=c++11

lab9: lab9Driver.o RBTree.o binaryTree.o
		g++ -o lab9 lab9Driver.o RBTree.o binaryTree.o

RBTree.o: RBTree.cpp
		g++ -c -g	RBTree.cpp

binaryTree.o: binaryTree.cpp
		g++ -c -g binaryTree.cpp

lab9Driver.o: lab9Driver.cpp
		g++ -c -g lab9Driver.cpp

clean:
				rm *.o lab9
