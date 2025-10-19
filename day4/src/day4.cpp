#include "day4.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "grid.hpp"
#include "point.hpp"

std::pair<std::string, std::string> Day4::run(const std::filesystem::path& input_path)
{
    Grid grid = parse_input(input_path);
    int result_part1 = part1(grid);
    int result_part2 = part2(grid);
    return {std::to_string(result_part1), std::to_string(result_part2)};
}

Grid Day4::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::string contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();
    return Grid(contents);
}

int Day4::part1(const Grid& grid)
{
    unsigned int occurrences = 0;
    std::vector<Point> x_positions = grid.get_points_by_char('X');
    for (const auto& point : x_positions)
    {
        for (const auto& direction : DIRECTIONS_ALL)
        {
            std::vector<Point> points_in_dir = grid.get_points_in_direction(point, direction, 4);
            std::string direction_str = grid.points_to_string(points_in_dir);
            if (direction_str == "XMAS")
            {
                ++occurrences;
            }
        }
    }
    return occurrences;
}

int Day4::part2(const Grid& grid)
{
    unsigned int occurrences = 0;
    std::vector<Point> a_positions = grid.get_points_by_char('A');
    for (const auto& point : a_positions)
    {
        // Grab string from top-left to bottom-right and top-right to bottom-left and check for "MAS" or "SAM"
        Point corner_1 = point + Point{-1, -1};
        Point corner_2 = point + Point{1, -1};
        if (!grid.in_bounds(corner_1.x, corner_1.y) || !grid.in_bounds(corner_2.x, corner_2.y))
        {
            continue;
        }
        std::string diag1 = grid.points_to_string(grid.get_points_in_direction(corner_1, Point{1, 1}, 3));
        std::string diag2 = grid.points_to_string(grid.get_points_in_direction(corner_2, Point{-1, 1}, 3));
        bool diag1_valid = (diag1 == "MAS" || diag1 == "SAM");
        bool diag2_valid = (diag2 == "MAS" || diag2 == "SAM");
        if (diag1_valid && diag2_valid)
        {
            occurrences += 1;
        }
    }
    return occurrences;
}
