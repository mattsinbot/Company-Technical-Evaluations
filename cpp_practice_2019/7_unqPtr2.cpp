/******************************************************************************
                              Online C++ Compiler.
                           Unique Pointer Code Example
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <memory> // This is for smart pointers

using namespace std;


// Another function taking unique pointer as input
int bFunc(const std::unique_ptr<double[]> &testB, const int* sz_arr){
    int size_arr = *sz_arr;
    for (int i = size_arr-10; i < size_arr; i++) {
        testB[i] = 10*i;
    }
}


// Function taking unique pointer as input
int aFunc(const std::unique_ptr<double[]> &testA, const int* sz){
    
    // Store values
    for (int i= 0; i < *sz; i++) {
        testA[i] = (double) i;
    }
    
    bFunc(testA, sz);
    
    return 0;
}

int main()
{
    /////////////////////////////////
    // cout<<"Hello World";
    int* correctUsage = new int[20];
    *correctUsage = 100;
    *(correctUsage+1) = 200;
    
    cout << *(correctUsage+1) << endl;
    delete correctUsage;
    
    /////////////////////////////////
    class FreeStoreInt
    {
        private:
            int* ptr;
            
        public:
            FreeStoreInt(int* mInt) {
                ptr = mInt;
                cout << "FreeStoreInt type object created" << endl;
            }
            
        ~FreeStoreInt() {
            delete ptr;
            cout << "FreeStoreInt type object deleted" << endl;
        }
        
        int* get() {
            return ptr;
        }
    };
    cout << "Hello world !!!!" << endl;
    
    // FreeStoreInt test = new int(10);
        
    //////////////////////////////////////////////////
    /// Unique Pointer //////////////////////////////
    ////////////////////////////////////////////////
    std::unique_ptr<int> test(new int(10));
    
    std::unique_ptr<double> smartPointers(new double(20.3));
    std::unique_ptr<std::string> are(new std::string("extremely"));
    std::unique_ptr<char> varsatile(new char('A'));
    
    int size_arr = 40;
    std::unique_ptr<double[]> testArray(new double[size_arr]);
    // aFunc(testArray, &size_arr);
    
    for (int i = 0; i < size_arr; i++) {
        cout << testArray[i] << endl;
    }
    
    return 0;
}
