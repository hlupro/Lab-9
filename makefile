lab9: lab9Driver.o RBTree.o
		g++ -o lab8 lab9Driver.o RBTree.o

lab9Driver.o: lab9Driver.cpp
		g++ -c -g lab9Driver.cpp

RBTree.o: RBTree.cpp
		g++ -c -g	RBTree.cpp

clean:
				rm *.o lab9
