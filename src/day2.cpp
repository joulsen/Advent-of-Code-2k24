#include "day2.hpp"
#include <filesystem>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

std::pair<std::string, std::string> Day2::run(const std::filesystem::path &input_path)
{
    auto reports = parse_input(input_path);
    int result_part1 = part1(reports);
    int result_part2 = part2(reports);
    return {std::to_string(result_part1), std::to_string(result_part2)};
}

std::vector<Report> Day2::parse_input(const std::filesystem::path &input_path)
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

int Day2::part1(const std::vector<Report> &reports)
{
    return std::count_if(reports.begin(), reports.end(), [](const Report &report)
                         { return report.is_safe(false); });
}

int Day2::part2(const std::vector<Report> &reports)
{
    return std::count_if(reports.begin(), reports.end(), [](const Report &report)
                         { return report.is_safe(true); });
}

Report::Report(std::string line)
{
    std::istringstream iss(line);
    int value;
    while (iss >> value)
    {
        m_levels.push_back(value);
    }
}

bool Report::within_threshold(int difference) const
{
    return (1 <= std::abs(difference) && std::abs(difference) <= 3);
}

bool Report::is_safe(bool dampen) const
{
    if (!dampen)
    {
        return check_safety(m_levels);
    }

    for (size_t i = 0; i < m_levels.size(); ++i)
    {
        std::vector<int> levels_missing_i;
        levels_missing_i.reserve(m_levels.size() - 1);
        for (size_t j = 0; j < m_levels.size(); ++j)
        {
            if (j != i)
            {
                levels_missing_i.push_back(m_levels[j]);
            }
        }
        if (check_safety(levels_missing_i))
        {
            return true;
        }
    }
    return false;
}

bool Report::check_safety(std::vector<int> levels) const
{
    bool increasing = (levels[1] > levels[0]);
    for (size_t i = 1; i < levels.size(); ++i)
    {
        bool monotonic = increasing ? (levels[i] > levels[i - 1]) : (levels[i] < levels[i - 1]);
        int difference = std::abs(levels[i] - levels[i - 1]);
        bool threshold_ok = (1 <= difference && difference <= 3);
        if (!monotonic || !threshold_ok)
        {
            return false;
        }
    }
    return true;
}