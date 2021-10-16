all: test

test: p2.o recursive.o simple_test.o
	g++ -o test p2.o recursive.o simple_test.o -Wall

p2.o: p2.cpp
	g++ -c p2.cpp -Wall

recursive.o: recursive.cpp
	g++ -c recursive.cpp -Wall

simple_test.o: simple_test.cpp
	g++ -c simple_test.cpp -Wall

clean:
	rm -f test *.o