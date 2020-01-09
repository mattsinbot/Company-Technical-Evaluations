#include <iostream>
using namespace std;

class polygon{
    private:
        double height;
        double width;
    public:
        /* Default constructor */
        polygon();

        /* Constructor */
        polygon(double, double);

        /* Area method */
        double area();
};

polygon::polygon(){
   height = 10.0;
   width = 10.0;
}

polygon::polygon(double a, double b){
    height = a;
    width = b;
}

double polygon::area(){
    return height*width;
}

int main() {
    polygon pg(5.0, 9.0);
    std::cout << "Area: " << pg.area() << endl;
    return 0;
}

