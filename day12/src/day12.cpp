#include "day12.hpp"

#include <string>
#include <unordered_set>
#include <vector>

#include "garden_plot.hpp"
#include "grid.hpp"

std::pair<std::string, std::string> Day12::run(const std::filesystem::path& input_path)
{
    Grid grid = parse_input(input_path);
    std::vector<GardenPlot> garden_plots = find_garden_plots(grid);
    uint64_t total_price_1 = 0;
    uint64_t total_price_2 = 0;

    for (const GardenPlot& plot : garden_plots)
    {
        total_price_1 += plot.get_price_1();
        total_price_2 += plot.get_price_2();
    }
    return {std::to_string(total_price_1), std::to_string(total_price_2)};
}

Grid Day12::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::string contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();
    return Grid(contents);
}

std::vector<GardenPlot> Day12::find_garden_plots(const Grid& grid)
{
    std::unordered_set<Point> unvisited = {};
    unvisited.reserve(grid.size());
    for (unsigned int x = 0; x < grid.cols(); ++x)
    {
        for (unsigned int y = 0; y < grid.rows(); ++y)
        {
            unvisited.insert(Point{static_cast<int>(x), static_cast<int>(y)});
        }
    }

    std::vector<GardenPlot> plots;
    while (!unvisited.empty())
    {
        Point start_point = *unvisited.begin();
        GardenPlot plot(grid, start_point);
        for (const Point& point : plot.get_points())
        {
            unvisited.erase(point);
        }
        plots.push_back(plot);
    }

    return plots;
}
