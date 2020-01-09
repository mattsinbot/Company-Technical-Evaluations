#include<iostream>
#include<cstdio>
using namespace std;

/* 
How to use assignment operator when class data containers has data allocated 
with using NEW.
*/

class Foo
{
public:
    int* data; int* array_data;
    
    Foo() { 
        data = new int(5); 
        array_data = new int[10];
    }
    
    void FillArray() {
        array_data[0] = 2000; array_data[1] = 4000;
    }
    
    void operator = (const Foo &F) {
        // std::cout << *(F.data) << std::endl;
        // std::cout << *(this->data) << std::endl;
        *(this->data) = *(F.data);
        for(int i = 0; i < 10; i++){
            this->array_data[i] = F.array_data[i];
        }
    }
    ~Foo() { delete data; delete[] array_data;}
};

int main()
{
    Foo a, b;
    std::cout << "initial a.data=" << *(a.data) << std::endl;
    
    // reassign a.data
    *(a.data) = 10; 
    std::cout << "new a.data=" << *(a.data) << std::endl;
    
    // call FillArray() method of object a
    a.FillArray();
    std::cout << a.array_data[0] << " " << a.array_data[1] << std::endl;
    
    // Assign values of a to b using assigment operator
    b = a;
    std::cout << b.array_data[0] << " " << b.array_data[1] << " " << b.array_data[2] << std::endl;
    
    return 0;
}