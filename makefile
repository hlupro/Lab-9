lab9: lab9Driver.o RBTree.o
		g++ -o lab9 lab9Driver.o RBTree.o

RBTree.o: RBTree.cpp
		g++ -c -g	RBTree.cpp

lab9Driver.o: lab9Driver.cpp
		g++ -c -g lab9Driver.cpp

clean:
				rm *.o lab9
