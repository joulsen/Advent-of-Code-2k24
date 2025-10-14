#include "day4.hpp"
#include "tilemap.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

std::pair<std::string, std::string> Day4::run(const std::filesystem::path &input_path)
{
    TileMap tile_map = parse_input(input_path);
    int result_part1 = part1(tile_map);
    int result_part2 = part2(tile_map);
    return {std::to_string(result_part1), std::to_string(result_part2)};
}

TileMap Day4::parse_input(const std::filesystem::path &input_path)
{
    std::ifstream input_file(input_path);
    std::string contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();
    return TileMap(contents);
}

int Day4::part1(const TileMap &tile_map)
{
    unsigned int occurrences = 0;
    std::vector<TileMap::Coord> x_positions = tile_map.find('X');
    for (const auto &[x_row, x_col] : x_positions)
    {
        for (int delta_row = -1; delta_row <= 1; ++delta_row)
        {
            for (int delta_col = -1; delta_col <= 1; ++delta_col)
            {
                std::string direction = tile_map.get_string_in_direction(x_row, x_col, {delta_row, delta_col}, 4);
                if (direction == "XMAS")
                {
                    ++occurrences;
                }
            }
        }
    }
    return occurrences;
}

int Day4::part2(const TileMap &tile_map)
{
    unsigned int occurrences = 0;
    std::vector<TileMap::Coord> a_positions = tile_map.find('A');
    for (const auto &[a_row, a_col] : a_positions)
    {
        std::string diag1 = tile_map.get_string_in_direction(a_row - 1, a_col - 1, {1, 1}, 3);
        std::string diag2 = tile_map.get_string_in_direction(a_row - 1, a_col + 1, {1, -1}, 3);
        if (diag1.length() == 3 && diag2.length() == 3 &&
            diag1[1] == 'A' && diag2[1] == 'A')
        {
            bool diag1_valid = (diag1 == "MAS" || diag1 == "SAM");
            bool diag2_valid = (diag2 == "MAS" || diag2 == "SAM");

            if (diag1_valid && diag2_valid)
            {
                occurrences += 1;
            }
        }
    }
    return occurrences;
}