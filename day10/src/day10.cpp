#include "day10.hpp"

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "grid.hpp"

std::pair<std::string, std::string> Day10::run(const std::filesystem::path& input_path)
{
    Grid grid = parse_input(input_path);
    const std::vector<Point>& starting_positions = grid.get_points_by_char('0');
    unsigned int total_trailheads = 0;
    unsigned int total_rating = 0;

    std::unordered_set<Point> reachable_nines;
    reachable_nines.reserve(grid.get_points_by_char('9').size());
    for (const Point& start : starting_positions)
    {
        reachable_nines.clear();
        unsigned int path_count = 0;
        traverse(grid, start, total_rating, reachable_nines);
        total_trailheads += reachable_nines.size();
    }

    return {std::to_string(total_trailheads), std::to_string(total_rating)};
}

Grid Day10::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::string contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();
    return Grid(contents);
}

void Day10::traverse(const Grid& grid, const Point& start, unsigned int& path_count, std::unordered_set<Point>& reachable_nines) const
{
    char start_char = grid.at(start);
    unsigned int trailheads = 0;
    for (const Point& neighbor : grid.get_neighbors_masked(start, {UP, DOWN, LEFT, RIGHT}))
    {
        char neighbor_char = grid.at(neighbor);
        if (neighbor_char == start_char + 1)
        {
            traverse(grid, neighbor, path_count, reachable_nines);
        }
    }
    if (start_char == '9')
    {
        reachable_nines.emplace(start);
        path_count++;
    }
}