//
// Created by puppybala on 2023.08.19.
//

#ifndef CPPCODE_KTHMINNUM_H
#define CPPCODE_KTHMINNUM_H
#include "vector"

class kthMinNum {
public :
    int quickSelect(std::vector<int>& nums, int l, int r, int k);
    inline int randomPartition(std::vector<int>& nums, int l, int r);
    inline int partition(std::vector<int>& nums, int l, int r);
    int findKthLargest(std::vector<int>& nums, int k);
};


#endif //CPPCODE_KTHMINNUM_H
