#ifndef AOC2024_TILEMAP_HPP
#define AOC2024_TILEMAP_HPP

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class TileMap
{
public:
    using Coord = std::pair<unsigned int, unsigned int>;
    using Tile = char;

    TileMap(const std::string& input);
    TileMap(const std::vector<std::string>& input);

    const Tile& at(unsigned int row, unsigned int col) const;
    const std::vector<Coord>& find(Tile tile) const;

    std::unordered_map<Tile, std::vector<Coord>> get_neighbors(unsigned int row, unsigned int col) const;
    std::unordered_map<Tile, std::vector<Coord>>
    get_neighbors_in_directions(unsigned int row, unsigned int col, const std::vector<Coord>& directions) const;
    std::string get_string_in_direction(unsigned int start_row, unsigned int start_col, Coord direction, unsigned int length) const;

private:
    bool in_bounds(int row, int col) const;

    int m_rows;
    int m_cols;
    std::vector<std::vector<Tile>> m_tiles;
    std::unordered_map<Tile, std::vector<Coord>> m_tile_positions;  // For O(1) lookup
};

#endif  // AOC2024_TILEMAP_HPP