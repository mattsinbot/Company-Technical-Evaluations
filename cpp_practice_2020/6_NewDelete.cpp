#include<iostream>
#include<cstdio>
using namespace std;

/* 
This function describes how to use new and delete in C++ for assigning memories 
for a variable and an array type. Also note the destructor method of the Foo class.
*/

class Foo
{
public:
    int* data; int* array_data;
    Foo() { data = new int(5); array_data = new int[10];}
    void FillArray() {
        array_data[0] = 2000; array_data[1] = 4000;
    }
    ~Foo() { delete data; delete[] array_data;}
};

int main()
{
    Foo a;
    std::cout << "data=" << *(a.data) << std::endl;
    
    *(a.data) = 10;
    std::cout << "data=" << *(a.data) << std::endl;
    
    a.FillArray();
    std::cout << a.array_data[0] << " " << a.array_data[1] << std::endl;
    
    return 0;
}