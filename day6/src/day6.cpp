#include "day6.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "grid.hpp"
#include "guard.hpp"
#include "point.hpp"

std::pair<std::string, std::string> Day6::run(const std::filesystem::path& input_path)
{
    auto [grid, start_position] = parse_input(input_path);
    std::pair<int, PatrolStates> result_part1 = part1(grid, start_position);
    int result_part2 = part2(grid, start_position, result_part1.second);
    return {std::to_string(result_part1.first), std::to_string(result_part2)};
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

std::pair<int, PatrolStates> Day6::part1(Grid& grid, Point& start_position)
{
    Guard guard(grid, start_position);
    std::unordered_map<Point, Point> patrol_states;
    patrol_states.reserve(grid.size());
    PatrolResult result = guard.patrol(patrol_states);
    if (result != PatrolResult::OUT_OF_BOUNDS)
    {
        throw std::runtime_error("Guard did not exit the grid bounds as expected");
    }
    return {static_cast<int>(patrol_states.size()), patrol_states};
}

int Day6::part2(Grid& grid, Point& start_position, const PatrolStates& initial_patrol_states)
{
    Guard guard(grid, start_position);
    int obstacles_causing_loops = 0;
    PatrolStates iteration_patrol_states;
    for (const auto& [position, direction] : initial_patrol_states)
    {
        iteration_patrol_states.clear();
        iteration_patrol_states.reserve(grid.size());
        if (position == start_position) continue;
        guard.set_position(start_position);
        grid.set(position, '#');
        PatrolResult result = guard.patrol(iteration_patrol_states);
        if (result == PatrolResult::LOOP)
        {
            obstacles_causing_loops++;
        }
        grid.set(position, '.');
    }
    return obstacles_causing_loops;
}