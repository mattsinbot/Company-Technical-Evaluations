CC=g++
CFLAGS= -Wall -std=c++11 -I ../include
LDLIBS= -pthread

all: hello

hello: fun1.o main.o
	$(CC) $(CFLAGS) main.o fun1.o -o hello

fun1.o: pt2d.cpp
	$(CC) $(CFLAGS) pt2d.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp $(LDLIBS)

clean:
	rm -rf *o hello
