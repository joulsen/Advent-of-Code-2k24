#include "day1.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

std::pair<std::string, std::string> Day1::run(const std::filesystem::path& input_path)
{
    std::vector<int> column_1;
    std::vector<int> column_2;
    parse_input(input_path, column_1, column_2);
    int result_part1 = part1(column_1, column_2);
    int result_part2 = part2(column_1, column_2);
    return {std::to_string(result_part1), std::to_string(result_part2)};
}

void Day1::parse_input(const std::filesystem::path& input_path, std::vector<int>& out_column_1, std::vector<int>& out_column_2)
{
    if (!std::filesystem::exists(input_path))
    {
        throw std::runtime_error("Input file does not exist");
    }
    std::ifstream input_file(input_path);
    for (std::string line; std::getline(input_file, line);)
    {
        size_t delimiter_pos = line.find(' ');
        if (delimiter_pos == std::string::npos)
        {
            throw std::runtime_error("Invalid input format");
        }
        out_column_1.push_back(std::stoi(line.substr(0, delimiter_pos)));
        out_column_2.push_back(std::stoi(line.substr(delimiter_pos + 1)));
    }
}

int Day1::part1(std::vector<int> column_1, std::vector<int> column_2)
{
    std::sort(column_1.begin(), column_1.end());
    std::sort(column_2.begin(), column_2.end());
    unsigned int distance = 0;
    for (size_t i = 0; i < column_1.size(); ++i)
    {
        distance += std::abs(column_1[i] - column_2[i]);
    }
    return distance;
}

int Day1::part2(std::vector<int> column_1, std::vector<int> column_2)
{
    int similarity_score = 0;
    for (const auto& val1 : column_1)
    {
        similarity_score += std::count(column_2.begin(), column_2.end(), val1) * val1;
    }
    return similarity_score;
}