/******************************************************************************
                           Unique Pointer Code Example
                              Author: Anirban Sinha
                              Date: July 29th, 2018
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <memory> // This is for smart pointers

using namespace std;


// Another function taking unique pointer as input
int bFunc(const std::unique_ptr<double[]>& testB, const int* sz_arr){
    int size_arr = *sz_arr;
    for (int i = size_arr-10; i < size_arr; i++) {
        testB[i] = 10*i;
    }
}


// Function taking unique pointer as input
int aFunc(const std::unique_ptr<double[]>& testA, const int* sz){
    
    // Store values
    for (int i= 0; i < *sz; i++) {
        testA[i] = (double) i;
    }
    
    bFunc(testA, sz);
    
    return 0;
}

class newData{
    private:
        int size_arr;
        std::unique_ptr<double[]> ptrArray;
    public:
        newData() {};
        newData(int szArray, std::unique_ptr<double[]>& ptrAr) {
            size_arr = szArray;
            //ptrArray = ptrAr; /*Fail to compile. unq_ptr can not be copied*/
            ptrArray = std::move(ptrAr);
        }
        /*newData(newData& bData) {
            //size_arr = bData->sz();
            ptrArray = bData->getData();
        }*/
        void prntCont(){
            for (int i = 0; i < size_arr; i++) {
                cout << ptrArray[i] << endl;
            }
        }
        void getData(std::unique_ptr<double[]>& pt) {
            pt = std::move(ptrArray);
        }
    //~newData() {
    //    delete ptrArray; // No need of destructor, unq_ptr does it under the
                           // hood
    //}
};

int main()
{     
    //////////////////////////////////////////////////
    ///                Unique Pointer              ///
    //////////////////////////////////////////////////    
    int size_arr = 40;
    std::unique_ptr<double[]> testArray(new double[size_arr]);
    std::unique_ptr<double[]> testArray1;

    // Calling aFunc store values in testArray
    aFunc(testArray, &size_arr);
    
    // Create an object of newData
    // newData a = newData(size_arr, testArray);
    // a.getData();

    // Object b takes ownership of unique pointer from testArray
    newData* b = new newData(size_arr, testArray);
    b->prntCont();
    
    // owner ship handed over to testArray1 from testArray
    b->getData(testArray1);
    delete b;

    for (int i = 0; i < size_arr; i++) {
        cout << i << " element : " << testArray1[i] << endl;
    }

    // newData* c = new newData(b);
    

    // delete b;

    return 0;
}
