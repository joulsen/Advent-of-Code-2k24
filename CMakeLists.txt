cmake_minimum_required(VERSION 3.16)
project(aoc2024)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(aoc2024
    src/main.cpp
    src/day1.cpp
    src/day2.cpp
)

target_include_directories(aoc2024 PRIVATE include)
