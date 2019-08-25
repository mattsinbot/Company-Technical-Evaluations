#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

using namespace std;

class pt2d{
  private:
    int x, y;
  public:
    pt2d() {x = 0; y = 0;}
    pt2d(int a, int b) {x =a; y = b;}
    int getpt_x(){return x;}
    int getpt_y(){return y;}
};

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
  public:
    World(vector<vector<char>> &nmap) {map_ = nmap;}
    void display() {
      for (int i = 0; i < map_.size(); i++) {
          for (int j = 0; j < map_[i].size(); j++) {
            cout << map_[i][j] << " ";
          }
          cout << "\n" << endl;
      }
    }
};

int main(int argc, char** argv) 
{ 
  /* Given */
  int run_itr = 100;
  char map[7][7] = {
    {'1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '1', '1'},
  };

  int grid_height = sizeof(map)/sizeof(map[0]);
  int grid_width = sizeof(map[0])/sizeof(map[0][0]);

  vector<vector<char>> vec_map;
  for(int i = 0; i < grid_height; i++) {
    vector<char> map_row;
    for (int j = 0; j < grid_width; j++) {
      map_row.push_back(map[i][j]);
    }
    vec_map.push_back(map_row);
  }

  /* Instantiate World */
  World w(vec_map);
  w.display();

  /* Instantiate Robot */
  Robot rbt = Robot(5, 5);

  /* Check if robot has been spawned into a free cell */
  char str1 = map[rbt.get_px()][rbt.get_py()];
  if (str1 != '0') {
    std::cout << "Invalid robot spawning position" << std::endl;
    std::cout << "Exiting" << std::endl;
    return 0;
  }

  /* Run the robot autonomously */
  int count = 0;
  bool run_flag = true;
  bool found_free = false;
  int search_dir = 0;
  while(run_flag) {
    pt2d current_rbt;    
    found_free = false;
    while(!found_free) {
      current_rbt = rbt.move(search_dir);
      char str1 = map[current_rbt.getpt_x()][current_rbt.getpt_y()];
      if (current_rbt.getpt_x() >= 1 && current_rbt.getpt_y() >= 1 && str1!= '1') {
        found_free = true;}
      else {
        search_dir = rand() % 4;}
    }
    rbt.update_state(current_rbt);
 
    std::cout << "robot x: " << current_rbt.getpt_x() 
              << "robot y: " << current_rbt.getpt_y() << std::endl;

    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 7; j++) {
        if (i == current_rbt.getpt_x() && j == current_rbt.getpt_y()) 
          {std::cout << 'A' << " ";}
        else 
          {std::cout << map[i][j] << " ";}
       }
      std::cout << "\n" << std::endl;
    }
   std::cout << "==============" << std::endl;
   std::cout << count << std::endl;
   count++;

   if (count > run_itr) 
     {run_flag = false;}

   /* Wait for 500 ms  before clear screen*/
   std::this_thread::sleep_for(std::chrono::milliseconds(500));
   system("clear");
  }
}
