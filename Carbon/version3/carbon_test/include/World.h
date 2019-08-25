#ifndef WORLD_H_
#define WORLD_H_

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <map>
// #include "pt2d.h"
#include "Robot.h"

using namespace std;

class World{
  private:
    vector<vector<char>> map_;
    vector<Robot> robotRegister;
    map<char, int> robotNameId;
    int robotCount = 0;
  public:    
    World(vector<vector<char>> &nmap) {map_ = nmap;} /* Constructor */    
    bool addRobot(int, int, char);                   /* addRobot  method */    
    void run(char, int);                             /* run method */    
    void display(int);                               /* display method */
};

#endif
