#ifndef AOC2024_DAY2_HPP
#define AOC2024_DAY2_HPP

#include <vector>

#include "day.hpp"
#include "report.hpp"

class Day2 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 2; }
    std::string get_day_name() const override { return "Red-Nosed Reports"; }

private:
    std::vector<Report> parse_input(const std::filesystem::path& input_path);
    int part1(const std::vector<Report>& reports);
    int part2(const std::vector<Report>& reports);
};

REGISTER_DAY(Day2, 2)

#endif  // AOC2024_DAY2_HPP
