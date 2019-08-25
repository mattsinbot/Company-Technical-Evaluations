#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <map>

using namespace std;

class pt2d{
  private:
    int x, y;
  public:
    pt2d() {x = 0; y = 0;}
    pt2d(int a, int b) {x =a; y = b;}
    int getpt_x();
    int getpt_y();
};

int pt2d::getpt_x(){return x;}
int pt2d::getpt_y(){return y;}

class Robot{
  private:
    int rx;
    int ry;
  public:
    Robot(int x, int y) {rx = x; ry = y;}
    pt2d move(int srch_dir) {
      if (srch_dir == 0) {pt2d pt(rx, ry+1); return pt;}      // move right
      else if (srch_dir == 1) {pt2d pt(rx, ry-1); return pt;} // move left
      else if (srch_dir == 2) {pt2d pt(rx-1, ry); return pt;} // move up
      else {pt2d pt(rx+1, ry); return pt;}                    // move down
    }
    void update_state(pt2d pt) {rx = pt.getpt_x(); ry = pt.getpt_y();}
    int get_px() {return rx;}
    int get_py() {return ry;}
};

class World{
  private:
    vector<vector<char>> map_;
    vector<Robot> robotRegister;
    map<char, int> robotNameId;
    int robotCount = 0;
  public:
    /* Constructor */
    World(vector<vector<char>> &nmap) {map_ = nmap;}

    /* addRobot  method */
    bool addRobot(int x, int y, char name) {
      char str1 = map_[x][y];
      if (str1 != '0') {
        std::cout << "Invalid robot spawning position" << std::endl;
        return false;
       }
      robotRegister.push_back(Robot(x, y));
      map_[x][y] = name;
      robotNameId[name] = robotCount;
      robotCount += 1;
      return true;
    }

    /* run method */
    void run(char name, int run_itr) {
      int id = robotNameId[name];
      cout << "Robot Id: " << id << endl;

      int count = 0;
      bool run_flag = true;
      bool found_free = false;
      int search_dir = 0;

      while(run_flag) {
        pt2d current_rbt;    
        found_free = false;
        while(!found_free) {
          current_rbt = robotRegister[id].move(search_dir);
          char str1 = map_[current_rbt.getpt_x()][current_rbt.getpt_y()];
          if (current_rbt.getpt_x() >= 1 && current_rbt.getpt_y() >= 1 && str1 == '0') {
            found_free = true;}
          else {
            search_dir = rand() % 4;}
          }
        map_[robotRegister[id].get_px()][robotRegister[id].get_py()] = '0';
        robotRegister[id].update_state(current_rbt);
        map_[robotRegister[id].get_px()][robotRegister[id].get_py()] = name;
        count++;

        ///* Wait for 500 ms  before clear screen*/
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (count > run_itr) {run_flag = false;}
       }
    }

    /* display method */
    void display(int run_itr) {
      int count = 0;
      while (count < run_itr) {
        for (int i = 0; i < (int)map_.size(); i++) {
            for (int j = 0; j < (int)map_[i].size(); j++) {
              cout << map_[i][j] << " ";
            }
            cout << "\n" << endl;
        }
        cout << "================" << endl;
        count++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        system("clear");
      }
    }
};
