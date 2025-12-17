#ifndef AOC2024_DAY14_HPP
#define AOC2024_DAY14_HPP

#include <string>
#include <vector>

#include "day.hpp"
#include "robot.hpp"

class Day14 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 14; }
    std::string get_day_name() const override { return "Restroom Redoubt"; }

private:
    RobotContainer parse_input(const std::filesystem::path& input_path) const;
    uint64_t part1(RobotContainer& robots) const;
    uint64_t part2(RobotContainer& robots) const;
    void print_robots(const RobotContainer& robots) const;
};

REGISTER_DAY(Day14, 14)
#endif  // AOC2024_DAY14_HPP