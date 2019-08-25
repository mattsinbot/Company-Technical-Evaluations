#include <iostream>
#include <thread>

// https://stackoverflow.com/questions/54740276/threading-program-runs-with-g-but-not-with-gcc

class foo
{
public:
    void bar(int loop_num)
    {
        for (int i = 0; i < loop_num; ++i) {
            std::cout << "Thread 3 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};
 
int main()
{
    int n = 0;
    foo f;
    std::thread t5(&foo::bar, &f, 5); // t5 runs foo::bar() on object f
    
    t5.join();
}
