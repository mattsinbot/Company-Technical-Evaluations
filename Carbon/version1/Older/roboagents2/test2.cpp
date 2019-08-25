#include <iostream>
#include <thread>
using namespace std;

class myshape{
  protected:
    double height;
    double width;
  public:
    myshape(double h, double w) {height = h; width = w;}
    void print_descpirtion() {cout << "Computes area of a rectangle" << endl;}
    void display_area(int num_loop) {
      for (int i = 0; i < num_loop; i++) {
        cout << "Area: " << height*width << endl;
      }
    }
    
};

int main(int argc, char** argv) 
{
  myshape s(5, 2);
  s.print_descpirtion();
  std::thread t1(&myshape::display_area, s, 100);
  t1.join();
}

