#include<iostream>
using namespace std;

int BinarySearchRecursive(int arr[], int start_index, int end_index, int target) {
    int mid_index = (start_index + end_index)/2;
    if (start_index <= end_index) {
        if (arr[mid_index] > target) {
            end_index = mid_index - 1;
        }
        else if (arr[mid_index] < target) {
            start_index = mid_index + 1;
        }
        else {
            return mid_index;
        }
        return BinarySearchRecursive(arr, start_index, end_index, target);
    }
    return -1;
}

int main() {
    int arr[] = {1, 3, 7, 15, 18, 20, 25, 33, 36, 40};
    int n = sizeof(arr)/sizeof(arr[0]);
    int target = 33;
    int index = BinarySearchRecursive(arr, 0, n-1, target);
    
    if (index == -1) {std::cout << target << " does not exists in the array.\n";}
    else{std::cout << target << " located at index " << index << std::endl;}
    return 0;
}


