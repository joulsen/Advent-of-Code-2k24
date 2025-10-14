#include "day3.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

std::pair<std::string, std::string> Day3::run(const std::filesystem::path& input_path)
{
    std::string input = parse_input(input_path);
    int result_part1 = part1(input);
    int result_part2 = part2(input);
    return {std::to_string(result_part1), std::to_string(result_part2)};
};

std::string Day3::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream file(input_path);
    std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return contents;
}

int Day3::part1(const std::string& contents)
{
    std::regex mul_regex(R"(mul\((\d+),(\d+)\))");
    auto matches_begin = std::sregex_iterator(contents.begin(), contents.end(), mul_regex);
    auto matches_end = std::sregex_iterator();
    unsigned int result = 0;
    for (auto it = matches_begin; it != matches_end; ++it)
    {
        std::smatch match = *it;
        unsigned int a = std::stoi(match[1].str());
        unsigned int b = std::stoi(match[2].str());
        result += a * b;
    }
    return result;
}

int Day3::part2(const std::string& contents)
{
    unsigned int result = 0;
    bool doing = true;
    unsigned int position = 0;
    while (true)
    {
        std::regex toggle_regex((doing) ? R"(don't\(\))" : R"(do\(\))");
        std::smatch match;
        std::regex_search(contents.cbegin() + position, contents.cend(), match, toggle_regex);
        unsigned int end_position = (match.position() == std::string::npos) ? contents.size() : position + match.position();
        if (doing)
        {
            result += part1(contents.substr(position, end_position - position));
        }
        if (end_position == contents.size())
        {
            break;
        }
        doing = !doing;
        position = end_position + match.length();
    }
    return result;
}