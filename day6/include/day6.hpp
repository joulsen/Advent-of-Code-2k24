#ifndef AOC2024_DAY6_HPP
#define AOC2024_DAY6_HPP

#include <string>
#include <vector>

#include "day.hpp"
#include "grid.hpp"
#include "guard.hpp"

class Day6 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 6; }
    std::string get_day_name() const override { return "Guard Gallivant"; }

private:
    std::pair<Grid, Point> parse_input(const std::filesystem::path& input_path);
    int part1(Grid& grid, Point& start_position);
    int part2(Grid& grid, Point& start_position);
};

REGISTER_DAY(Day6, 6)
#endif  // AOC2024_DAY6_HPP