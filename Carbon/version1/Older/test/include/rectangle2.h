#include <iostream>
using namespace std;

class Rectangle{
  protected:
    double height;
    double width;
  public:
    void setHeight(double h);
    void setWidth(double w);
    double area();
};

void Rectangle::setHeight(double h) {height = h;}
void Rectangle::setWidth(double w) {width = w;}
double Rectangle::area() {return height*width;}
