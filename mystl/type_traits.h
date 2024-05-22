//
// Created by puppy on 5/21/24.
//

#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

// 提取类型信息
#include <type_traits>
namespace mystl {
    template <class T, T v>
    struct m_integral_constant {
        static constexpr T value = v;
    };

    template <bool b>
    using m_bool_constant =  m_integral_constant<bool, b>;
    typedef m_bool_constant<true> m_true_type;
    typedef m_bool_constant<false> m_false_type;
    // is pair
    template <class T1, class T2>
    struct pair;

    template <class T>
    struct is_pair : mystl::m_false_type{};
    // 特化
    template <class T1, class T2>
    struct is_pair<mystl::pair<T1, T2>> : mystl::m_true_type{};

}

#endif //TYPE_TRAITS_H
