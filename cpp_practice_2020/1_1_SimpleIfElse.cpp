#include<iostream>
using namespace std;

/* Write a C++ application that, for each number between 1 and 100, prints Pick 
if it is divisible by 3, Nik if divisible by 5, and PickNick if divisible by 
both. */

void print_picknick() {
    int count1 = 0; int count2 = 0; int count3 = 0;
    for (int i = 0; i < 100; i++) {
        if (i%3 == 0 && i%5 == 0) {std::cout << "PickNick" << std::endl; count1++;}
        if (i%3 == 0) {std::cout << "Pick" << std::endl; count2++;}
        if (i%5 == 0) {std::cout << "Nick" << std::endl; count3++;}
    }
    std::cout << "count1: " << count1 << std::endl;
    std::cout << "count2: " << count2 << std::endl;
    std::cout << "count3: " << count3 << std::endl;
}

int main() {
    print_picknick();
    return 0;
}


