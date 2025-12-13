#ifndef AOC2024_DAY10_HPP
#define AOC2024_DAY10_HPP

#include <string>
#include <unordered_set>
#include <vector>

#include "day.hpp"
#include "grid.hpp"

class Day10 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 10; }
    std::string get_day_name() const override { return "Hoof It"; }

private:
    Grid parse_input(const std::filesystem::path& input_path);
    void traverse(const Grid& grid, const Point& start, unsigned int& path_count, std::unordered_set<Point>& reachable_nines) const;
};

REGISTER_DAY(Day10, 10)
#endif  // AOC2024_DAY10_HPP