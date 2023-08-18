//
// Created by puppybala on 2023.08.19.
//

#include "quickSort.h"
#include "iostream"
using namespace std;

void quickSort(int *arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && arr[j] >= pivot) j--;
        arr[i] = arr[j];
        while (i < j && arr[i] <= pivot) i++;
        arr[j] = arr[i];
    }
    arr[i] = pivot;
    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}
int main() {
    int arr[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    quickSort(arr, 0, 9);
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}