#include <fstream>
#include <iostream>
#include <string>


using namespace std;

int main() {
    string fl_name = "data.txt";
    ifstream myfile;
    myfile.open(fl_name);
    
    if (!myfile.is_open()){
        std::cout << "File is not opened\n";
        exit(1);
    }

    double val;
    while (myfile >> val) {
        std::cout << val << " ";
    }
    std::cout << "\n";
    
    return 0;
}

