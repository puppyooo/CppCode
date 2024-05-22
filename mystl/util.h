//
// Created by puppy on 5/22/24.
//

#ifndef UTIL_H
#define UTIL_H

#include <cstddef>

#include "type_traits.h"

namespace mystl {
    // move
    template <class T>
    typename std::remove_reference<T>::type&& move(T&& arg) noexcept {
        return static_cast<typename std::remove_reference<T>::type&&>(arg);
    }

    // forward
    template <class T>
    T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
        return static_cast<T&&>(arg);
    }
    template <class T>
    T&& forward(typename std::remove_reference<T>::type&& arg) noexcept {
        static_assert(std::is_lvalue_reference<T>::value, "bad forward");
        return static_cast<T&&>(arg);
    }

    // swap
    template <class Tp>
    void swap(Tp& lhs, Tp& rhs) {
        auto tmp(mystl::move(lhs));
        lhs = mystl::move(rhs);
        rhs = mystl::move(tmp);
    }

    template <class forwardIter1, class forwardIter2>
    forwardIter2 swap_range(forwardIter1 first1, forwardIter1 last, forwardIter2 first2) {
        for(; first1 != last; ++first1, ++first2) {
            mystl::swap(*first1, *first2);
        }
        return first2;
    }

    template <class Tp, size_t N>
    void swap(Tp(&a)[N], Tp(&b)[N]) noexcept {
        mystl::swap_range(a, a + N, b);
    }

    // pair
    template <class Ty1, class Ty2>
    struct pair {
        typedef Ty1     first_type;
        typedef Ty2     second_tpye;

        first_type      first;
        second_tpye     second;

        // construct
        template <class Other1 = Ty1, class Other2 = Ty2,
            typename = typename std::enable_if<
                std::is_default_constructible<Other1>::value && std::is_default_constructible<Other2>::value>
        > constexpr pair() : first(), second() {}

        // implicit
        template <class U1 = Ty1, class U2 = Ty2,
            typename std::enable_if<
            std::is_copy_constructible<U1>::value &&
            std::is_copy_constructible<U2>::value &&
            std::is_convertible<const U1&, Ty1>::value &&
            std::is_convertible<const U2&, Ty1>::value, int>::type = 0>
        constexpr pair(const Ty1& a, const Ty2& b) : first(a), second(b){}
        // explicit



    };



}

#endif //UTIL_H
