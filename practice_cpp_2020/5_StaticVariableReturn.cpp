#include<cstdio>

/* 
This code is a perfect example of using static variables. In C/C++, you are 
not allowed to return any variable which are of non-static type. If you want to
return a non-static type variable from a function to the main() function, then 
the variable dies after the function execution, so you get segmentatio-fault while
trying accessing outside the function. But static variables are given memory until 
the end of the whole program.
*/  

int* area(int length, int width){
    static int area = length*width;
    return &area;
}

int main(){
    int* comp_area = area(5, 6);
    printf("area=%i\n", *comp_area);
    return 0;
}