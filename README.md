# Advent of Code 2024
My submissions for the Advent of Code 2024 (almost a year late).

Written in C++.

# Building and using
There are no dependencies other than a C++17 compatible compiler and CMake.

To run my code, clone this repository and build it. On Linux, that could look like this:

```sh
git clone https://github.com/joulsen/Advent-of-Code-2k24.git
cd Advent-of-Code-2k24
mkdir out
cd out
cmake ..
cmake --build
```

Then run the executable, and a nice help menu should pop up:
```
Usage: ./aoc2024 <action>
Actions:
  run <day> <input_file>     Run the solution with the specified input file
  list                       List available days
```

# Generator
Inside `helpers/` resides a generator, which I use to generate the skeleton for each day.
This tool is not required for building or running the submissions, but if you want to run it, there is a `requirements.txt` that you can use to satisfy the dependencies.