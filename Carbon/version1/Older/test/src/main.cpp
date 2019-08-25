#include "rectangle.h"
// #include "rectangle2.h"

int main() {
    Rectangle r;
    r.setHeight(6.0);
    r.setWidth(2.0);
    std::cout << "Area of Rectangle: " << r.area() << std::endl;
    return 0;
}
