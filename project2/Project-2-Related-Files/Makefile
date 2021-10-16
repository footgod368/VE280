all: test

test: p2.o recursive.o treeins_test.o
	g++ -o test p2.o recursive.o treeins_test.o -Wall

p2.o: p2.cpp
	g++ -c p2.cpp -Wall

recursive.o: recursive.cpp
	g++ -c recursive.cpp -Wall

treeins_test.p: treeins_test.cpp
	g++ -c treeins_test.cpp -Wall

clean:
	rm -f test *.o