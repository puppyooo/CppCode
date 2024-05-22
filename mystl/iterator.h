//
// Created by puppy on 5/21/24.
//

#ifndef ITERATOR_H
#define ITERATOR_H

// 迭代器设计 包含一些模版结构和全局函数
#include <cstddef>
#include "type_traits.h"

namespace mystl {
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag : public input_iterator_tag{};
    struct bidirectional_iterator_tag : public forward_iterator_tag{};
    struct random_access_iterator_tag : public bidirectional_iterator_tag{};

    template <class category, class T, class Distance = ptrdiff_t, class Point = T*, class Reference = T&>
    struct iterator {
        typedef category        iterator_category;
        typedef T               value_type;
        typedef Distance        difference_type;
        typedef Point           pointer;
        typedef Reference       reference;
    };

    // iterator traits

    template <class T>
    struct has_iterator_cat {
    private:
        struct two {char a; char b;};
        template <class U> static two test(...);
        template <class U> static char test(typename U::iterator_category* = 0);
    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(char);
    };

    template <class Iterator, bool>
    struct iterator_traits_impl{};

    template <class Iterator>
    struct iterator_traits_impl<Iterator, true> {
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::difference_type      difference_type;
    };

    template <class Iterator, bool>
    struct iterator_traits_helper{};

    template <class Iterator>
    struct iterator_traits_helper<Iterator, true> : public iterator_traits_impl<Iterator,
    std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
    std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>{};

    // 萃取迭代器特性
    template <class Iterator>
    struct iterator_traits : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value>{};
    // 针对原生指针的偏特化版本
    template <class T>
    struct iterator_traits<T*> {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef ptrdiff_t                   difference_type;
    };

    template <class T>
    struct iterator_traits<const T*> {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
        typedef ptrdiff_t                   difference_type;
    };

    template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
    struct has_iterator_cat_of : public m_bool_constant<std::is_convertible<typename iterator_traits<T>::iterator_category, U>::value>{};

    //萃取某种迭代器
    template <class T, class U>
    struct has_iterator_cat_of<T, U, false> : public m_false_type{};

    template <class Iter>
    struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag>{};

    template <class Iter>
    struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag>{};

    template <class Iter>
    struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag>{};

    template <class Iter>
    struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag>{};

    template <class Iter>
    struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag>{};

    template <class Iterator>
    struct is_iterator : public has_iterator_cat_of<is_input_iterator<Iterator>::value || is_output_iterator<Iterator>::value>{};

    //萃取某个迭代器的category
    template <class Iterator>
    typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator&) {
        typedef typename iterator_traits<Iterator>::iterator_category Category;
        return Category();
    }

    // 萃取某个迭代器的distance_type
    template <class Iterator>
    typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator&) {
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }

    // 萃取某个迭代器的value_type
    template <class Iterator>
    typename iterator_traits<Iterator>::value_type*
    value_type(const Iterator&) {
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }

    // 计算迭代器之间的距离
    // distance的input_iterator_tag版本
    template <class inputIterator>
    typename iterator_traits<inputIterator>::difference_type
    distance_dispatch(inputIterator first, inputIterator last, input_iterator_tag) {
        typename iterator_traits<inputIterator>::difference_type n = 0;
        while (first != last) {
            ++first;
            ++n;
        }
        return n;
    }
    // distance的random_access_iterator_tag版本
    template <class randomIter>
    typename iterator_traits<randomIter>::difference_type
    distance_dispatch(randomIter first, randomIter last, random_access_iterator_tag) {
        return last - first;
    }

    template <class inputIter>
    typename iterator_traits<inputIter>::difference_type
    distance(inputIter first, inputIter last) {
        return distance_dispatch(first, last, iterator_category(first));
    }

    // 以下函数让迭代器前进n个距离
    // advance的input_iterator_tag版本
    template <class inputIter, class Distance>
    void advance_dispatch(inputIter& i, Distance n, input_iterator_tag) {
        while(n--) ++i;
    }
    // advance的bidirectional_iterator_tag版本
    template <class inputIter, class Distance>
    void advance_dispatch(inputIter& i, Distance n, bidirectional_iterator_tag) {
        if(n >= 0) {
            while(n--) ++i;
        } else {
            while(n++) --i;
        }
    }

    // advance的random_access_iterator_tag版本
    template <class randomIter, class Distance>
    void advance_dispatch(randomIter& i, Distance n, random_access_iterator_tag) {
        i += n;
    }
    template <class inputIter, class Distance>
    void advance(inputIter& i, Distance n) {
        return advance_dispatch(i, n, iterator_category(i));
    }

    // 模版类：reverse_iterator
    // 代表反向迭代器，前进为后退，后退为前进
    template <class Iterator>
    class reverse_iterator {
    private:
        Iterator current;
    public:
        typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename iterator_traits<Iterator>::value_type          value_type;
        typedef typename iterator_traits<Iterator>::pointer             pointer;
        typedef typename iterator_traits<Iterator>::reference           reference;
        typedef typename iterator_traits<Iterator>::difference_type     difference_type;

        typedef Iterator                                                iterator_type;
        typedef reverse_iterator<Iterator>                              self;

        // 构造函数
        reverse_iterator(){}
        explicit reverse_iterator(iterator_type i) : current(i){}
        reverse_iterator(const self& rhs) : current(rhs.current){}

        //取出正向迭代器
        iterator_type base() const {
            return current;
        }
        // 重载操作符
        reference operator*() const {
            auto tmp = current;
            return *--tmp;
        }
        pointer operator->() const {
            return &(operator*());
        }
        self& operator++() {
            --current;
            return *this;
        }
        self operator++(int) {
            self tmp = *this;
            --current;
            return tmp;
        }
        self& operator--() {
            ++current;
            return *this;
        }
        self operator--(int) {
            self tmp = *this;
            ++current;
            return tmp;
        }
        self& operator+=(difference_type n) {
            current -= n;
            return *this;
        }
        self operator+(difference_type n) const {
            return self(current - n);
        }
        self& operator-=(difference_type n) const {
            current += n;
            return *this;
        }
        self operator-(difference_type n) const {
            return self(current + n);
        }
        reference operator[](difference_type n) const {
            return *(*this + n);
        }
    };

    // 重载operator-
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() - lhs.base();
    }
    // 重载比较运算符
    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return lhs.base() == rhs.base();
    }
    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() < lhs.base();
    }
    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return !(lhs == rhs);
    }
    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs < lhs;
    }
    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return !(rhs < lhs);
    }
    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return !(lhs < rhs);
    }

}

#endif //ITERATOR_H
