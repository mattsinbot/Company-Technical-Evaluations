#include <iostream>
using namespace std;

#ifndef RECTANGLE
#define RECTANGLE

class Rectangle{
  protected:
    double height;
    double width;
  public:
    void setHeight(double h);
    void setWidth(double w);
    double area();
};

#endif
