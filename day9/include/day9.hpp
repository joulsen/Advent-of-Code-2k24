#ifndef AOC2024_DAY9_HPP
#define AOC2024_DAY9_HPP

#include <string>
#include <vector>

#include "blocks.hpp"
#include "day.hpp"

class Day9 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 9; }
    std::string get_day_name() const override { return "Disk Fragmenter"; }

private:
    DiskMap::Blocks parse_input(const std::filesystem::path& input_path);
};

REGISTER_DAY(Day9, 9)
#endif  // AOC2024_DAY9_HPP