#include<iostream>
using namespace std;

void pass_array_method1(int arr[], int sz_arr) {
    std::cout << "pass_array_method1: ";
    // int array_length = sizeof(arr)/sizeof(arr[0]);
    for (int  i = 0; i < sz_arr; i++){
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

void pass_array_method2(int* arr, int sz_arr) {
    std::cout << "pass_array_method2: ";
    for (int i = 0; i < sz_arr; i++) {
        std::cout << *(arr + i) << " ";
    }
    std::cout << "\n";
}

double* returning_array() {
    // Inplace initialization of array
    static double my_arr2[] = {10, 200, 300}; // Note the static keyword. C does not allow non static arrays to return
    for (int i = 0; i < 3; i++)
        std::cout << my_arr2[i] << " ";
    std::cout << "\n";
    return my_arr2;
}

int main() {
    // creating simple array
    int size_array = 5;
    int my_arr1[size_array];
    my_arr1[0] = 0; my_arr1[1] = 1; my_arr1[2] = 2; my_arr1[3] = 3; my_arr1[4] = 4;
    
    // Find the size of an array (this method does not work with array pointers)
    std::cout << "size of my_arr1 = " << sizeof(my_arr1)/sizeof(my_arr1[0]) << std::endl;
    
    // call pass_array_method1 (pass by value)
    pass_array_method1(my_arr1, size_array);
    
    // call pass_array_method2 (pass by reference)
    pass_array_method2(my_arr1, size_array);
    
    // call returning_array
    double* returned_arr = returning_array();
    std::cout << *returned_arr << " ";
    std::cout << "\n";
    
    return 0;
}