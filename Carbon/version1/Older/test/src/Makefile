CC=g++
CFLAGS= -Wall -std=c++11 -I ../include
LDLIBS= -pthread

rectTest: main.o rectangle.o
	$(CC) $(CFLAGS)  main.o rectangle.o -o rectTest

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

rectangle.o: rectangle.cpp
	$(CC) $(CFLAGS) -c rectangle.cpp

clean:
	rm -f core *.o
