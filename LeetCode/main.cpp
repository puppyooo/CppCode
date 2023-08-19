//
// Created by puppybala on 2023.08.19.
//
#include "kthMinNum.h"
#include <iostream>
using namespace std;

int main() {
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    kthMinNum kthMinNum;
    cout << kthMinNum.findKthLargest(nums, 2) << endl;
    cout << "Hello, World!" << endl;
    return 0;
}