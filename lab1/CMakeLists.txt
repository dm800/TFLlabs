cmake_minimum_required(VERSION 3.16)
project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab1Fuzz
        Fuzz.cpp
)

add_executable(lab1Meta
        Metamorph.cpp
)
