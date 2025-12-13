#ifndef AOC2024_DAY11_HPP
#define AOC2024_DAY11_HPP

#include <string>
#include <vector>

#include "day.hpp"

using blink_t = uint8_t;
using stone_t = uint64_t;

class Day11 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 11; }
    std::string get_day_name() const override { return "Plutonian Pebbles"; }

    using blink_cache = std::unordered_map<std::string, std::unordered_map<blink_t, stone_t>>;

private:
    std::vector<std::string> parse_input(const std::filesystem::path& input_path);
    stone_t blink_single(std::string stone, blink_t blinks, blink_cache& cache) const;
    stone_t blink_list(const std::vector<std::string>& stones, blink_t blinks, blink_cache& cache) const;
};

REGISTER_DAY(Day11, 11)
#endif  // AOC2024_DAY11_HPP