#include<iostream>
#include<cstdio>
using namespace std;

template<class T> 
class Logger
{
    public:
        Logger (const T& input);
        void print() const;
    private:
        T data;
};

int main() {
    Logger<int>* myLogger(5);
    return 0;
}