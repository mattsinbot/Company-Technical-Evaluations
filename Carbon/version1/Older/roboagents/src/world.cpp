#include <iostream>
#include <thread>
#include <chrono>
#include "world.h"

World::World(char map[7][7]) {  
    for (int i = 0; i < 7; i++) {    
        for (int j = 0; j < 7; j++) {      
            map_[i][j] = map[i][j];    
        }  
     }
}

bool World::addRobot(int row, int col) {  
    map_[row][col] = 'A';  
    return true;
}

void World::run() {
  while (true) {    
      display();    
      std::this_thread::sleep_for(std::chrono::milliseconds(100));  
   }  
}

void World::display() {  
    // "Clear" screen  
    for (int i = 0; i < 20; i++)
        std::cout << std::endl; 
    for (int i = 0; i < 7; i++) {    
        for (int j = 0; j < 7; j++) {      
            std::cout << map_[i][j];    
        }    
        std::cout << std::endl;  
     }
}
