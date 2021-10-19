all: myTest

myTest: p2.o recursive.o myTest.o
	g++ -o myTest p2.o recursive.o myTest.o

myTest.o: myTest.cpp
	# g++ -c myTest.cpp

p2.o: p2.cpp
	g++ -c p2.cpp

recursive.o: recursive.cpp
	g++ -c recursive.cpp

clean:
	rm -f myTest *.o