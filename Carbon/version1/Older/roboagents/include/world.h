#ifndef WORLD_H_

#define WORLD_H_


#include <vector>

#include "robot.h"



// Forward declaration

class Robot;


// Define and implement the following class. Feel free to change the given
// interfaces and data structures to better match your design


class World {
 public:
  World(char map[7][7]);
  
    bool addRobot(int row, int col);
  void run();
  
    void display();

 private:
  
    char map_[7][7];

};


#endif
