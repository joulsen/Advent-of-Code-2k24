#ifndef AOC2024_DAY12_HPP
#define AOC2024_DAY12_HPP

#include <string>
#include <vector>

#include "day.hpp"
#include "garden_plot.hpp"
#include "grid.hpp"

class Day12 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 12; }
    std::string get_day_name() const override { return "Garden Groups"; }

private:
    Grid parse_input(const std::filesystem::path& input_path);
    std::vector<GardenPlot> find_garden_plots(const Grid& grid);
};

REGISTER_DAY(Day12, 12)
#endif  // AOC2024_DAY12_HPP