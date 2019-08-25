#include "world.h"

int main(int argc, char** argv) 
{ 
  /* Given */
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
  world w(vec_map);
  w.addRobot(1, 1, 'A');
  w.addRobot(4, 1, 'B');

  /* Run each robot in a different thread */
  std::thread t1(&world::run, &w, 'A', 100);
  std::thread t2(&world::run, &w, 'B', 100);
  
  /* Visualize in a separate thread */
  std::thread t3(&world::display, &w, 100);

  t1.join();
  t2.join();
  t3.join();
  
  return 0;
}
