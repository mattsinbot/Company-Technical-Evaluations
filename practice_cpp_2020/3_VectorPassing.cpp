#include<iostream>
#include <vector>
using namespace std;

// passing a vector by value
std::vector<double> pass_vector_method1 (std::vector<double> v){
    for (auto it = v.cbegin(); it != v.cend(); it++)
        std::cout << *it << " ";
    std::cout << "\n";
    
    // add a few elements
    v.push_back(1000);
    v.push_back(2000);
    
    return v;
}

// passing a vector by reference
void pass_vector_method2 (std::vector<double>* v) {
    for (auto it = v->cbegin(); it != v->cend(); it++)
        std::cout << *it << " ";
    std::cout << "\n";
    
    // add a few more elements
    v->push_back(100);
    v->push_back(200);
}

int main(){
    std::vector<double> vec = {1, 2, 3};
    // Add more elements using for loop
    for (int i = 0; i < 10; i++){
        vec.push_back(2*i);
    }
    
    // Method-1: pass the vector to a function (by value)
    vec = pass_vector_method1(vec);
    
    // Method-2: pass the vector to a function (by reference)
    pass_vector_method2(&vec);
    
    // Loop through the elements of the vector
    for (auto i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";
}
