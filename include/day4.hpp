#ifndef AOC2024_DAY4_HPP
#define AOC2024_DAY4_HPP

#include "day.hpp"
#include "tilemap.hpp"

class Day4 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path &input_path) override;
    unsigned int get_day_number() const override { return 4; }
    std::string get_day_name() const override { return "Ceres Search"; }

private:
    TileMap parse_input(const std::filesystem::path &input_path);
    int part1(const TileMap &tile_map);
    int part2(const TileMap &tile_map);
};

REGISTER_DAY(Day4, 4)

#endif // AOC2024_DAY4_HPP