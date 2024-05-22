//
// Created by puppy on 5/21/24.
//

#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include <new>
#include "type_traits.h"
#include "iterator.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)
#endif

namespace mystl {
    template <class Ty>
    void construct(Ty* ptr) {
        ::new((void*)ptr) Ty();
    }

    template <class Ty1, class Ty2>
    void construct(Ty1* ptr, const Ty2& value) {
        ::new((void*)ptr) Ty1(value);
    }
    template <class Ty, class... Args>
    void construct(Ty* ptr, Args&&... args) {
        ::new((void*)ptr) Ty(mystl::forward<Args>(args)...);
    }

    // 析构函数
    template <class Ty>
    void destroy_one(Ty*, std::true_type) {}

    template <class Ty>
    void destroy_one(Ty* pointer, std::false_type) {
        if (pointer != nullptr) {
            pointer->~Ty();
        }
    }

    template <class forwardIter>
    void destroy_cat(forwardIter, forwardIter, std::true_type) {}

    template <class forwardIter>
    void destroy_cat(forwardIter first, forwardIter last, std::false_type) {
        for(; first != last; ++first) {
            destroy(&*first);
        }
    }

    template <class Ty>
    void destroy(Ty* pointer) {
        destroy_one(pointer, std::is_trivially_destructible<Ty>{});
    }

    template <class forwardIter>
    void destroy(forwardIter first, forwardIter last) {
        destroy_cat(first, last, std::is_trivially_destructible<typename iterator_traits<forwardIter>::value_type>{});
    }

}


#endif //CONSTRUCT_H
