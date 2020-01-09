#include<iostream>
#include<memory>

using namespace std;

class Education {
    private:
        string degree;
    public:
        Education() {
            std::cout << "Education type created with no degree name" << std::endl;
            degree = "nodeg";
        }
        Education(string deg_name) {
            std::cout << "Education type created with degree " << deg_name << std::endl;
            degree = deg_name;
        }
        void HaveEdu() {
            std::cout << "I have education" << std::endl;
        }
        ~Education() {
            std::cout << "Object deleted with degree " << degree << std::endl;
        }
};

/* Building an object on heap */
void test1() {
    std::cout << "test1:" << std::endl; 
    Education* edu = new Education("B.Music");
    edu->HaveEdu();
    delete edu;
}

/* Building an object on heap using unique_ptr */
void test2() {
    std::cout << "test2:" << std::endl;
    unique_ptr<Education> edu2 (new Education("B.Architect"));  // Notice the initialization syntax
    edu2->HaveEdu();
}

/* Reset method of unique_ptr */
void test3() {
    std::cout << "test3:" << std::endl;
    unique_ptr<Education> edu3 (new Education("B.Stat"));
    edu3->HaveEdu();
    
    /* reset unique_ptr pointer */
    edu3.reset();
    
    /* Check if it becomes NULL pointer */
    if (!edu3) {
        std::cout << "edu3 is a NULL pointer" << std::endl; 
    }
}

/* Release method of unique_ptr */
void test4() {
    std::cout << "test4:" << std::endl;
    unique_ptr<Education> edu3 (new Education("B.Stat"));
    edu3->HaveEdu();
    
    /* reset unique_ptr pointer */
    Education* edu4 = edu3.release();    // memory will not be deleted manually
    std::cout << "edu3 owerership released" << std::endl;

   /* delete edu4 manually to recover memory */
   delete edu4;
}



int main() {
    /* call test1 */
    test1();
    std::cout << "===========================" << std::endl;

    /* call test2 */
    test2();
    std::cout << "===========================" << std::endl;

    /* call test3 */
    test3();
    std::cout << "===========================" << std::endl;

    /* call test4 */
    test4();
    std::cout << "===========================" << std::endl;

    return 0;
}
