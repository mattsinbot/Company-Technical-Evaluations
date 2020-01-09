# include <iostream>
using namespace std;


/*Method 1: insert data into an array*/ 
int insert_array_element1(int arr[], int* sz_arr) {
    for (int i = 0; i < *sz_arr; i++){
        arr[i] = 2*i + 1;
    }
    return 0;
}

/*Method 2: insert data into an array*/
int insert_array_element2(int* arr, int* sz_arr) {
    for (int i = 0; i < *sz_arr; i++){
        std::cout << *(arr + i) << " ";
    }
    std::cout << "\n";
    return 0;
}


int main(){
    /* create a double array*/
    int sz_arr = 10;
    int a_array[sz_arr];

    /* Call insert_array_elements */
    insert_array_element1(a_array, &sz_arr);
    insert_array_element2(a_array, &sz_arr);

    return 0;
}
