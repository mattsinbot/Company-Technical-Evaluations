CC=g++
CFLAGS= -Wall -std=c++11 -I ../include
LDLIBS= -pthread

all: main.o pt2d.o robot.o world.o
	$(CC) $(CFLAGS) main.o pt2d.o Robot.o World.o $(LDLIBS) -o main

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

pt2d.o: pt2d.cpp
	$(CC) $(CFLAGS) -c pt2d.cpp

robot.o: Robot.cpp
	$(CC) $(CFLAGS) -c Robot.cpp

world.o: World.cpp
	$(CC) $(CFLAGS) -c World.cpp

clean:
	rm -rf *o main
