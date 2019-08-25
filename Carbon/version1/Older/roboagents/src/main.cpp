#include "world.h"
#include "robot.h"


int main(int argc, char** argv) 
{
 // You should customize this data structure and the World constructor to
 // match your chosen data structure.  
  char map[7][7] = {
    {'1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '1', '1'},
  };  
  World w(map);  
  w.addRobot(1, 1);  
  w.run();
}
