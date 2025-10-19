#ifndef AOC2024_DAY4_HPP
#define AOC2024_DAY4_HPP

#include "day.hpp"
#include "grid.hpp"

class Day4 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 4; }
    std::string get_day_name() const override { return "Ceres Search"; }

private:
    Grid parse_input(const std::filesystem::path& input_path);
    int part1(const Grid& grid);
    int part2(const Grid& grid);
};

REGISTER_DAY(Day4, 4)

#endif  // AOC2024_DAY4_HPP