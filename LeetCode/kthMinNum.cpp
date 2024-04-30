//
// Created by puppybala on 2023.08.19.
//

#include "kthMinNum.h"

int kthMinNum::quickSelect(std::vector<int> &nums, int l, int r, int k) {
    int pos = kthMinNum::randomPartition(nums, l, r);
    if (pos == k) {
        return nums[pos];
    } else {
        return pos < k ? kthMinNum::quickSelect(nums, pos + 1, r, k) : kthMinNum::quickSelect(nums, l, pos - 1, k);
    }
}

int kthMinNum::randomPartition(std::vector<int> &nums, int l, int r) {
    int x = rand() % (r - l + 1) + l;
    std::swap(nums[x], nums[r]);
    return kthMinNum::partition(nums, l, r);
}

int kthMinNum::partition(std::vector<int> &nums, int l, int r) {
    int x = nums[r], i = l - 1;
    int a = 5;
    for (int j = l; j < r; ++j) {
        if (nums[j] <= x) {
            std::swap(nums[++i], nums[j]);
        }
    }
    std::swap(nums[i + 1], nums[r]);
    return i + 1;
}

int kthMinNum::findKthLargest(std::vector<int> &nums, int k) {
    srand(time(0));
    return kthMinNum::quickSelect(nums, 0, nums.size() - 1, k - 1);
}
