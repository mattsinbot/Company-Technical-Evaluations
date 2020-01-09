#include <iostream>
using namespace std;

class Shape{
  protected:
    double height;
    double width;
  public:
    void setHeight(double h) {height = h;}
    void setWidth(double w) {width = w;}
};

class Rectangle: public Shape{
  public:
    double compArea() {return height*width;}
};

int main() {
    Rectangle r;
    r.setHeight(6.0);
    r.setWidth(2.0);
    std::cout << "Area of Rectangle: " << r.compArea() << std::endl;
    return 0;
}

