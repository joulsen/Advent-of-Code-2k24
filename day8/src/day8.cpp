#include "day8.hpp"

#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "grid.hpp"

std::pair<std::string, std::string> Day8::run(const std::filesystem::path& input_path)
{
    Grid grid = parse_input(input_path);
    std::vector<std::vector<Point>> antenna_pairs = get_antenna_pairs(grid);
    unsigned int part1 = get_antinode_count(grid, antenna_pairs, 1, false);
    unsigned int part2 = get_antinode_count(grid, antenna_pairs, grid.max_dimension(), true);
    return {std::to_string(part1), std::to_string(part2)};
}

Grid Day8::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::string contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();
    return Grid(contents);
}

std::vector<std::vector<Point>> Day8::get_antenna_pairs(const Grid& grid)
{
    std::vector<std::vector<Point>> antenna_pairs;
    for (const auto& [character, positions] : grid.char_positions())
    {
        if (character == '.') continue;
        if (positions.size() < 2) continue;
        for (const Point& antenna1 : positions)
        {
            for (const Point& antenna2 : positions)
            {
                if (antenna1 == antenna2) continue;
                antenna_pairs.push_back({antenna1, antenna2});
            }
        }
    }
    return antenna_pairs;
}

unsigned int Day8::get_antinode_count(const Grid& grid,
                                      const std::vector<std::vector<Point>>& antenna_pairs,
                                      unsigned int search_limit,
                                      bool include_antennas_as_antinodes)
{
    std::vector<Point> candidates;
    candidates.reserve(search_limit * 2);

    std::unordered_set<Point> antinodes;
    antinodes.reserve(grid.size());

    for (const auto& antenna_pair : antenna_pairs)
    {
        Point diff = antenna_pair[1] - antenna_pair[0];

        candidates = grid.get_points_in_direction(antenna_pair[0] - diff, diff * -1, search_limit);
        antinodes.insert(candidates.begin(), candidates.end());

        candidates = grid.get_points_in_direction(antenna_pair[1] + diff, diff, search_limit);
        antinodes.insert(candidates.begin(), candidates.end());

        if (include_antennas_as_antinodes)
        {
            antinodes.insert(antenna_pair[0]);
            antinodes.insert(antenna_pair[1]);
        }
    }
    return static_cast<unsigned int>(antinodes.size());
}
