#include<iostream>
#include <list>
#include <vector>
using namespace std;

void create_list(){
    std::list<int> l = { 7, 5, 16, 8 };
    std::cout << l.size() << std::endl;
}

void create_vector(){
    std::vector<int> vec = {17, 15, 116, 18};
    vec.push_back(20);
    
    // Iterate through the vector
    for (int n :vec)
        std::cout << n << " ";
    std::cout << "\n";
    
    // Using iterator
    for (auto it = vec.cbegin(); it != vec.cend(); it++){
        std::cout << *it + 1 << " ";
    }
}

int main(){
    // Call create_list
    create_list();
    
    // Call create_vector
    create_vector();
}
