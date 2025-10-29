#ifndef AOC2024_DAY7_HPP
#define AOC2024_DAY7_HPP

#include <string>
#include <vector>

#include "day.hpp"
#include "equation.hpp"

class Day7 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 7; }
    std::string get_day_name() const override { return "Bridge Repair"; }

private:
    std::vector<Equation> parse_input(const std::filesystem::path& input_path);
    unsigned long long part1(const std::vector<Equation>& equations);
    unsigned long long part2(const std::vector<Equation>& equations);
};

REGISTER_DAY(Day7, 7)
#endif  // AOC2024_DAY7_HPP