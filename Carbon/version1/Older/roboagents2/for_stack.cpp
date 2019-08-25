#include <iostream>
#include <vector>
using namespace std;

class foo{
  private:
    vector<vector<char>> b;
  public:
    foo(vector<vector<char>> &n){
      b = n;
    }
    void print_foo() {
      cout << b.size() << endl;
      for (int i = 0; i < b.size(); i++) {
          for (int j = 0; j < b[i].size(); j++) {
            cout << b[i][j];
          }
          cout << endl;
      }
    }
};

int main(int argc, char** argv) {
  char pp[4][4] = {
    {'1', '1', '1', '1'},
    {'1', '0', '0', '0'},
    {'1', '0', '0', '0'},
    {'1', '0', '0', '1'},
  };

  vector<vector<char>> p;
  for(int i = 0; i < 4; i++) {
    vector<char> m_row;
    for (int j = 0; j < 4; j++) {
      m_row.push_back(pp[i][j]);
    }
    p.push_back(m_row);
  }

  foo a(p);
  a.print_foo();
}
