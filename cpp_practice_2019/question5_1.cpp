#include <iostream>
using namespace std;


template<typename T> 
class Logger
{
    public:
        Logger (const T& input);
        void print() const;
    private:
        T data;
};


// Part B
void Logger<int>::print() {
    /* where data is a std vector and iterator of a vector is implemented*/
    for (auto itr=data.cbegin(); itr!=data.cend(); itr++) {
        std::cout << *itr << " ";
    }
}


// Part A
int main() {
    Logger<int>* myLogger(5);
    myLogger.print();

    return 0;
}
