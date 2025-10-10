#ifndef AOC2024_DAY1_HPP
#define AOC2024_DAY1_HPP

#include "day.hpp"
#include <vector>
#include <string>

class Day1 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path &input_path) override;
    unsigned int get_day_number() const override { return 1; }
    std::string get_day_name() const override { return "Historian Hysteria"; }

private:
    void parse_input(const std::filesystem::path &input_path, std::vector<int> &out_column_1, std::vector<int> &out_column_2);
    int part1(std::vector<int> column_1, std::vector<int> column_2);
    int part2(std::vector<int> column_1, std::vector<int> column_2);
};

REGISTER_DAY(Day1, 1)

#endif // AOC2024_DAY1_HPP