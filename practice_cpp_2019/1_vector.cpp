#include <iostream>
#include <vector>
using namespace std;

/* Method 1: Print vector elements using iterator. Vector is PASSED BY VALUE */
int vector_method1(const vector<double> vec){
    std::cout << "Inside vector_method1 : " << std::endl;
    // Print numbers in number_vec using vector.iterator
    for (auto itr=vec.cbegin(); itr!=vec.cend(); itr++) {
        std::cout << *itr << " ";
    }
    std::cout << "\n";
    return 0;
}

/* Method 2: Print vector elements using iterator. Vector is PASSED BY REFERENCE*/
int vector_method2(const vector<double>& vec){
    std::cout << "Inside vector_method2 : " << std::endl;
    // Print numbers in number_vec using vector.iterator
    for (auto itr=vec.cbegin(); itr!=vec.cend(); itr++) {
        std::cout << *itr << " ";
    }
    std::cout << "\n";
    return 0;
}

/* Method 3: Print vector elements using iterator. Vector is PASSED BY REFERENCE*/
int vector_method3(const vector<double>* vec){
    std::cout << "Inside vector_method3 : " << std::endl;
    // Print numbers in number_vec using vector.iterator
    for (int i = 0; i < vec->size(); i++) {
        std::cout << vec->at(i) << " ";
    }
    std::cout << "\n";
    return 0;
}

int main(){
    std::cout << "Hello world!!" << std::endl;

    // Create a vector of doubles
    vector<double> number_vec;
    number_vec = {1, 2, 3, 4};

    // Insert numbers into this vector
    for (int i = 0; i < 10; i++) {
        number_vec.push_back(2*i);
    }

    // Call custom function
    vector_method1(number_vec);
    vector_method2(number_vec);
    vector_method3(&number_vec);

    return 0;
}
