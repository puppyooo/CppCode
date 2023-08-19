cmake_minimum_required(VERSION 3.26)
project(CppCode)

set(CMAKE_CXX_STANDARD 14)

include_directories(LeetCode)

add_executable(CppCode
        LeetCode/kthMinNum.cpp
        LeetCode/kthMinNum.h
        LeetCode/main.cpp)
