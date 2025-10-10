cmake_minimum_required(VERSION 3.16)
project(aoc2024)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(aoc2024 ${SOURCES})

target_include_directories(aoc2024 PRIVATE include)
