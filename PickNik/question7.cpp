#include <iostream>
using namespace std;

int main() {
    for (int i = 0; i!= 100; i ++) {
        if(i%3==0 && i%5==0) std::cout << i << ":" << "PickNik" << std::endl;
        else if(i%3==0) std::cout << i << ":" << "Pick" << std::endl;
        else if(i%5==0) std::cout << i << ":" << "Nik" << std::endl;
    }
    return 0;
}
