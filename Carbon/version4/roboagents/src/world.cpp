#include "world.h"

bool world::addRobot(int x, int y, char name) {
  char str1 = map_[x][y];
  if (str1 != '0') {
    std::cout << "Invalid robot spawning position" << std::endl;
    return false;
  }
  robotRegister.push_back(robot(x, y));
  map_[x][y] = name;
  robotNameId[name] = robotCount;
  robotCount += 1;
  return true;
}

void world::run(char name, int run_itr) {
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

void world::display(int run_itr) {
  int count = 0;
  while (count < run_itr) {
    for (unsigned int i = 0; i < map_.size(); i++) {
        for (unsigned int j = 0; j < map_[i].size(); j++) {
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
