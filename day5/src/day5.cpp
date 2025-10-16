#include "day5.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

std::pair<std::string, std::string> Day5::run(const std::filesystem::path& input_path)
{
    auto [rules, jobs] = parse_input(input_path);
    auto [ordered_jobs, unordered_jobs] = jobs.get_ordered_and_unordered_jobs(rules);
    unordered_jobs.order_jobs(rules);
    int part1 = Jobs(ordered_jobs).sum_middle_pages();
    int part2 = Jobs(unordered_jobs).sum_middle_pages();
    return {std::to_string(part1), std::to_string(part2)};
}

std::pair<Rules, Jobs> Day5::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::string contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();

    size_t separator_pos = contents.find("\n\n");
    if (separator_pos == std::string::npos)
    {
        throw std::runtime_error("Invalid input format: missing separator between rules and jobs");
    }

    std::string rules_str = contents.substr(0, separator_pos);
    std::string jobs_str = contents.substr(separator_pos + 2);  // Skip the two newlines

    return {Rules(rules_str), Jobs(jobs_str)};
}
