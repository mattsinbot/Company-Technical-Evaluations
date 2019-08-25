#include<iostream>
using namespace std;

class Robot{
    private:
        int currentX;
        int currentY;
        int previousX = 0;
        int previousY = 5;
    public:
        Robot(int x, int y): currentX(x), currentY(y) {}
        void moveX(const int dx);
        void moveY(const int dy);
        void printCurrentCoordinates();
        void printPreviousCoordinates();
        void printLastMove();
};

void Robot::moveX(const int dx) {
    this->previousX = this->currentX;
    this->currentX += dx;
}

void Robot::moveY(const int dy) {
    this->previousY = this->currentY;
    this->currentY += dy;
}

void Robot::printCurrentCoordinates() {
    std::cout << this->currentX << ", " <<  this->currentY << std::endl;
}

void Robot::printPreviousCoordinates() {
    std::cout << this->previousX << ", " <<  this->previousY << std::endl;
}

void Robot::printLastMove() {
    if (this->currentX != this->previousX) {
        std::cout << currentX << "  " << (currentX - previousX) << std::endl;
        return;
    }
    
    if (this->currentY != this->previousY) {
        std::cout << currentY << "  " << (currentY - previousY) << std::endl;
        return;
    }
}


int main(int argc, char* argv[]) {
    Robot rbt1(10, 10);

    rbt1.printPreviousCoordinates();
    rbt1.printCurrentCoordinates();

    rbt1.moveX(1);
    rbt1.moveY(1);

    rbt1.printPreviousCoordinates();
    rbt1.printCurrentCoordinates();

    rbt1.printLastMove();
    return 0;
}

