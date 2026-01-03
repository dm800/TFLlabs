cmake_minimum_required(VERSION 3.16)
project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab2
        Fuzz.cpp
        NFA.cpp
        DFA.cpp
        AFA.cpp
)
