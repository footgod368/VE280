all: main

main: main.o study.o touch_fish.o
	g++ -o main main.o study.o touch_fish.o

main.o: main.cpp
	g++ -c main.cpp

study.o: study.cpp
	g++ -c study.cpp

touch_fish.o: touch_fish.cpp
	g++ -c touch_fish.cpp

clean:
	rm -f main *.o