#include "day14.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

std::pair<std::string, std::string> Day14::run(const std::filesystem::path& input_path)
{
    RobotContainer robot_container = parse_input(input_path);
    robot_container.move_all(100);
    uint64_t part1_result = robot_container.get_safety_factor();
    robot_container.reset();

    uint64_t max_clustering = 0;
    int32_t time_of_max_clustering = 0;

    for (int32_t t = 0; t < robot_container.get_lcm(); ++t)
    {
        robot_container.move_all(1);
        uint64_t clustering = robot_container.get_clustering_score();
        if (clustering > max_clustering)
        {
            max_clustering = clustering;
            time_of_max_clustering = t + 1;
        }
    }

    robot_container.reset(time_of_max_clustering);
    robot_container.print();

    return {std::to_string(part1_result), std::to_string(time_of_max_clustering)};
}

RobotContainer Day14::parse_input(const std::filesystem::path& input_path) const
{
    std::vector<Robot> robots;
    std::regex number_regex(R"((-?\d+))");
    std::ifstream input_file(input_path);
    std::string line;
    while (std::getline(input_file, line))
    {
        std::vector<int> numbers;
        std::sregex_iterator iter(line.begin(), line.end(), number_regex);
        std::sregex_iterator end;

        for (; iter != end; ++iter)
        {
            numbers.push_back(std::stoi(iter->str()));
        }
        assert(numbers.size() == 4);
        Point position{numbers[0], numbers[1]};
        Point velocity{numbers[2], numbers[3]};
        robots.emplace_back(position, velocity);
    }
    return RobotContainer(robots);
}
