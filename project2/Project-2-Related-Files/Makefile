all: test

test: p2.o recursive.o
	g++ -o test p2.o recursive.o

p2.o: p2.cpp
	g++ -c p2.cpp

recursive.o: recursive.cpp
	g++ -c recursive.cpp

clean:
	rm -f test *.o