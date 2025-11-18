cmake_minimum_required(VERSION 3.16)
project(aoc2024)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(add_aoc_days target_name day_list)
    set(day_sources cli/src/main.cpp)
    set(day_includes include)
    
    foreach(day ${day_list})
        list(APPEND day_sources day${day}/src/day${day}.cpp)
        list(APPEND day_includes day${day}/include)
    endforeach()
    
    add_executable(${target_name} ${day_sources})
    target_include_directories(${target_name} PRIVATE ${day_includes})
endfunction()

# Define which days to include
set(AOC_DAYS 1 2 3 4 5 6 7 8)

# Add all days
add_aoc_days(aoc2024 "${AOC_DAYS}")

target_include_directories(aoc2024 PRIVATE helpers/include)
