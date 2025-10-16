#include "day2.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

std::pair<std::string, std::string> Day2::run(const std::filesystem::path& input_path)
{
    auto reports = parse_input(input_path);
    int result_part1 = part1(reports);
    int result_part2 = part2(reports);
    return {std::to_string(result_part1), std::to_string(result_part2)};
}

std::vector<Report> Day2::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::vector<Report> reports;
    for (std::string line; std::getline(input_file, line);)
    {
        if (line.empty())
        {
            continue;
        }
        reports.emplace_back(line);
    }
    return reports;
}

int Day2::part1(const std::vector<Report>& reports)
{
    return std::count_if(reports.begin(), reports.end(), [](const Report& report) { return report.is_safe(false); });
}

int Day2::part2(const std::vector<Report>& reports)
{
    return std::count_if(reports.begin(), reports.end(), [](const Report& report) { return report.is_safe(true); });
}
