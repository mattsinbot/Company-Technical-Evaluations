#include <iostream>
#include <vector>
using namespace std;

class World{
  private:
    vector<vector<char>> map_;
  public:
    World(vector<vector<char>> &nmap) {map_ = nmap;}
    void display() {
      for (int i = 0; i < map_.size(); i++) {
          for (int j = 0; j < map_[i].size(); j++) {
            cout << map_[i][j];
          }
          cout << endl;
      }
    }
};

int main(int argc, char** argv) {
  char map[7][8] = {
    {'1', '1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1'},
  };
  int grid_height = sizeof(map)/sizeof(map[0]);
  int grid_width = sizeof(map[0])/sizeof(map[0][0]);
  vector<vector<char>> new_map;
  for(int i = 0; grid_height < 7; i++) {
    vector<char> map_row;
    for (int j = 0; grid_width < 8; j++) {
      map_row.push_back(map[i][j]);
    }
    new_map.push_back(map_row);
  }
  World w(new_map);
  w.display();

  std::cout << "map height: " << sizeof(map)/sizeof(map[0]) << " "
            << "map width: " << sizeof(map[0])/sizeof(map[0][0]) << endl;

  int count = 0;
  while(count < 10) {
    std::cout << rand() % 4 << std::endl;
    count++;
  }
}
