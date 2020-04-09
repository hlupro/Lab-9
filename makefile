

lab9: lab9Driver.o RBTree.o binaryTree.o
		g++ -std=c++11 -o lab9 lab9Driver.o RBTree.o binaryTree.o

RBTree.o: RBTree.cpp
		g++ -std=c++11 -c -g	RBTree.cpp

binaryTree.o: binaryTree.cpp
		g++ -std=c++11 -c -g binaryTree.cpp

lab9Driver.o: lab9Driver.cpp
		g++ -std=c++11 -c -g lab9Driver.cpp

clean:
				rm *.o lab9
