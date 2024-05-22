//
// Created by puppy on 5/22/24.
//

#ifndef NUMERIC_H
#define NUMERIC_H

#include "iterator.h"

namespace mystl {
    template <class inputIter, class T>
    T accumulate(inputIter first, inputIter last, T init) {
        for(; first != last; first++) {
            init += *first;
        }
        return init;
    }

    template <class inputIter, class outputIter>
    outputIter adjacent_difference(inputIter first, inputIter last, outputIter result) {
        if (first == last) return result;
        *result = *first;
        auto value = *first;
        while(++first != last) {
            auto tmp = *first;
            *++result = tmp - value;
            value = tmp;
        }
        return ++result;
    }

    template <class inputIter1, class inputIter2, class T>
    T inner_product(inputIter1 first1, inputIter1 last, inputIter2 first2, T init) {
        for(; first1 != last; ++first1, ++first2) {
            init += (*first1 * *first2);
        }
        return init;
    }

    template <class forwordIter, class T>
    void iota(forwordIter first, forwordIter last, T value) {
        while(first != last) {
            *first++ = value;
            ++value;
        }
    }

    template <class inputIter, class outputIter>
    outputIter partial_num(inputIter first, inputIter last, outputIter result) {
        if(first == last) return result;
        *result = *first;
        auto value = *first;
        while(++first != last) {
            value += *first;
            *++result = value;
        }
        return ++result;
    }

}


#endif //NUMERIC_H
