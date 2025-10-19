#include "day6.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "grid.hpp"
#include "guard.hpp"
#include "point.hpp"

std::pair<std::string, std::string> Day6::run(const std::filesystem::path& input_path)
{
    auto [grid, start_position] = parse_input(input_path);
    int result_part1 = part1(grid, start_position);
    int result_part2 = part2(grid, start_position);
    return {std::to_string(result_part1), std::to_string(result_part2)};
}

std::pair<Grid, Point> Day6::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::string contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();
    Grid grid(contents);

    std::vector<Point> guard_start_positions = grid.get_points_by_char('^');
    if (guard_start_positions.size() != 1)
    {
        throw std::runtime_error("Expected exactly one guard start position marked by '^'");
    }
    return {grid, guard_start_positions[0]};
}

int Day6::part1(Grid& grid, Point& start_position)
{
    Guard guard(grid, start_position);
    auto [result, visited_positions] = guard.patrol();
    return static_cast<int>(visited_positions.size());
}

int Day6::part2(Grid& grid, Point& start_position)
{
    Guard guard(grid, start_position);
    auto [result, visited_positions] = guard.patrol();

    int obstacles_causing_loops = 0;
    for (const Point& pos : visited_positions)
    {
        if (pos == start_position) continue;
        guard.set_position(start_position);
        grid.set(pos, '#');
        auto [result, _] = guard.patrol();
        if (result == PatrolResult::LOOP)
        {
            obstacles_causing_loops++;
        }
        grid.set(pos, '.');
    }
    return obstacles_causing_loops;
}