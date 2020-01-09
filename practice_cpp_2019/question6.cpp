#include <iostream>
using namespace std;

class Joint {
    public:
        Joint() : position(2.0) {}
        double getPosition() const {return position;}
    protected:
        double position;
};

class RevoluteJoint: public Joint {
    public:
        double squared() {return position*position;}
};

int main() {
    RevoluteJoint rj;
    std::cout << rj.squared() << std::endl;
    
    return 0;
}
