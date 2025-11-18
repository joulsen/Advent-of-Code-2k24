#ifndef AOC2024_DAY8_HPP
#define AOC2024_DAY8_HPP

#include <string>
#include <vector>

#include "day.hpp"
#include "grid.hpp"

class Day8 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 8; }
    std::string get_day_name() const override { return "Resonant Collinearity"; }

private:
    Grid parse_input(const std::filesystem::path& input_path);
    std::vector<std::vector<Point>> get_antenna_pairs(const Grid& grid);
    unsigned int get_antinode_count(const Grid& grid,
                                    const std::vector<std::vector<Point>>& antenna_pairs,
                                    unsigned int search_limit,
                                    bool include_antennas_as_antinodes);
};

REGISTER_DAY(Day8, 8)
#endif  // AOC2024_DAY8_HPP