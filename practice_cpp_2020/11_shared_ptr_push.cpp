#include <iostream>
#include <memory>
#include <queue>
using namespace std;

int main() {
    shared_ptr<int> pt (new int(10));
    std::cout << *pt << std::endl;

    queue<shared_ptr<int>> Q;
    Q.push(pt);
    
    Q.pop();

    std::cout << *pt << std::endl;   
}
