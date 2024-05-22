cmake_minimum_required(VERSION 3.26)
project(CppCode)

set(CMAKE_CXX_STANDARD 14)

include_directories(LeetCode)

add_executable(CppCode
        LeetCode/kthMinNum.cpp
        LeetCode/kthMinNum.h
        main.cpp
        Huawei/test.cpp
        mystl/construct.h
        mystl/type_traits.h
        mystl/iterator.h
        mystl/numeric.h
        mystl/util.h
        mystl/exceptdef.h
        mystl/astring.h
        mystl/basic_string.h
        mystl/memory.h
        mystl/functional.h
        mystl/algobase.h)
