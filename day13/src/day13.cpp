#include "day13.hpp"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::pair<std::string, std::string> Day13::run(const std::filesystem::path& input_path)
{
    std::vector<ClawMachine> machines = parse_input(input_path);
    int64_t total_cost = 0;
    for (const ClawMachine& machine : machines)
    {
        auto cost = machine.get_cost();
        if (cost)
        {
            total_cost += *cost;
        }
    }

    int64_t total_offset_cost = 0;
    for (const ClawMachine& machine : machines)
    {
        auto cost = machine.get_cost({10000000000000, 10000000000000});
        if (cost)
        {
            total_offset_cost += *cost;
        }
    }

    return {std::to_string(total_cost), std::to_string(total_offset_cost)};
}

std::vector<ClawMachine> Day13::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::string line;
    std::vector<ClawMachine> machines;
    std::regex line_regex(R"(X=?([-+]?\d+), Y=?([-+]?\d+))");
    std::smatch match;
    IntPair a_button, b_button, prize_position;

    while (true)
    {
        std::getline(input_file, line);
        if (line.empty())
        {
            continue;
        }
        std::regex_search(line, match, line_regex);
        a_button = {std::stoll(match[1]), std::stoll(match[2])};

        std::getline(input_file, line);
        std::regex_search(line, match, line_regex);
        b_button = {std::stoll(match[1]), std::stoll(match[2])};

        std::getline(input_file, line);
        std::regex_search(line, match, line_regex);
        prize_position = {std::stoll(match[1]), std::stoll(match[2])};
        machines.emplace_back(a_button, b_button, prize_position);

        std::getline(input_file, line);

        if (input_file.eof())
        {
            break;
        }
    }
    input_file.close();
    return machines;
}