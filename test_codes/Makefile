all: test

test: test.o
	g++ -Wall -o test test.o

test.o: test.cpp
	g++ -Wall -c test.cpp

clean:
	rm -f test *.o