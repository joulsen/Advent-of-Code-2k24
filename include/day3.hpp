#ifndef AOC2024_DAY3_HPP
#define AOC2024_DAY3_HPP

#include <string>

#include "day.hpp"

class Day3 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 3; }
    std::string get_day_name() const override { return "Mull It Over"; }

private:
    std::string parse_input(const std::filesystem::path& input_path);
    int part1(const std::string& contents);
    int part2(const std::string& contents);
};

REGISTER_DAY(Day3, 3)

#endif  // AOC2024_DAY3_HPP