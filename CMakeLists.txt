cmake_minimum_required(VERSION 3.16)
project(aoc2024)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/day1.cpp
    src/day2.cpp
    src/day3.cpp
    src/day4.cpp
)

add_executable(aoc2024 ${SOURCES})

target_include_directories(aoc2024 PRIVATE include)
