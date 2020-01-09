#include<iostream>
using namespace std;

class Joint {
public:
    Joint() : position(2.0) { }
    double getPosition() const {return position;}
protected:
    double position;
};

/* RevoluteJoint1 inherits Joint */
class RevoluteJoint1 : public Joint {
public:
    double squared() {
        return position*position;
    }
};

/* RevoluteJoint2 uses Joint as composition */
class RevoluteJoint2 {
public:
    RevoluteJoint2() { 
        Joint j; 
        pos = j.getPosition(); 
    }
    
    double squared() {
        return pos*pos;
    }
    double pos;
};

int main() {
    
    RevoluteJoint1 rjt;
    std::cout << "RevoluteJoint1::square position: " << rjt.squared() << std::endl;
    
    RevoluteJoint1 rjt2;
    std::cout << "RevoluteJoint2::square position: " << rjt2.squared() << std::endl;
}
