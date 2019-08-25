CC=g++
CFLAGS= -Wall -std=c++11 -I ../include
LDLIBS= -pthread

all: main2.o
	$(CC) main2.o -o hello

main2.o: main.cpp
	$(CC) $(CFLAGS) main.cpp $(LDLIBS)

clean:
	rm -rf *o hello


