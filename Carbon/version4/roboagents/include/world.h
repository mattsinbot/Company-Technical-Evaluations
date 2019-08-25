#ifndef WORLD_H_
#define WORLD_H_

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <map>
#include "robot.h"

using namespace std;

class world{
  private:
    vector<vector<char>> map_;
    vector<robot> robotRegister;
    map<char, int> robotNameId;
    int robotCount = 0;
  public:    
    world(vector<vector<char>> &nmap) {map_ = nmap;} /* Constructor */    
    bool addRobot(int, int, char);                   /* addRobot  method */    
    void run(char, int);                             /* run method */    
    void display(int);                               /* display method */
};

#endif
