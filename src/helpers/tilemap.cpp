#include "tilemap.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using Coord = TileMap::Coord;
using Tile = TileMap::Tile;

TileMap::TileMap(const std::string& input)
{
    if (input.empty()) throw std::invalid_argument("Input cannot be empty");
    std::vector<std::string> lines;
    std::istringstream iss(input);
    std::string line;
    while (std::getline(iss, line))
    {
        lines.push_back(line);
    }
    *this = TileMap(lines);
}

TileMap::TileMap(const std::vector<std::string>& input)
{
    if (input.empty()) throw std::invalid_argument("Input cannot be empty");
    m_rows = input.size();
    m_cols = input[0].size();
    m_tiles.resize(m_rows, std::vector<Tile>(m_cols));

    for (unsigned int r = 0; r < m_rows; ++r)
    {
        if (input[r].size() != m_cols) throw std::invalid_argument("All rows must have the same number of columns");
        for (unsigned int c = 0; c < m_cols; ++c)
        {
            Tile tile = input[r][c];
            m_tiles[r][c] = tile;
            m_tile_positions[tile].emplace_back(r, c);
        }
    }
}

const Tile& TileMap::at(unsigned int row, unsigned int col) const
{
    if (row >= m_rows || col >= m_cols) throw std::out_of_range("Coordinates out of bounds");
    return m_tiles[row][col];
}

const std::vector<Coord>& TileMap::find(Tile tile) const
{
    static const std::vector<Coord> empty;
    auto it = m_tile_positions.find(tile);
    if (it != m_tile_positions.end())
    {
        return it->second;
    }
    return empty;
}

std::unordered_map<Tile, std::vector<Coord>> TileMap::get_neighbors(unsigned int row, unsigned int col) const
{
    std::unordered_map<Tile, std::vector<Coord>> neighbors;
    for (int delta_row = -1; delta_row <= 1; ++delta_row)
    {
        for (int delta_col = -1; delta_col <= 1; ++delta_col)
        {
            if (delta_row == 0 && delta_col == 0) continue;
            int new_row = static_cast<int>(row) + delta_row;
            int new_col = static_cast<int>(col) + delta_col;
            if (in_bounds(new_row, new_col))
            {
                neighbors[m_tiles[new_row][new_col]].emplace_back(new_row, new_col);
            }
        }
    }
    return neighbors;
}

std::unordered_map<Tile, std::vector<Coord>>
TileMap::get_neighbors_in_directions(unsigned int row, unsigned int col, const std::vector<Coord>& directions) const
{
    std::unordered_map<Tile, std::vector<Coord>> neighbors;
    for (const auto& [delta_row, delta_col] : directions)
    {
        int new_row = static_cast<int>(row) + delta_row;
        int new_col = static_cast<int>(col) + delta_col;
        if (in_bounds(new_row, new_col))
        {
            neighbors[m_tiles[new_row][new_col]].emplace_back(new_row, new_col);
        }
    }
    return neighbors;
}

std::string TileMap::get_string_in_direction(unsigned int start_row, unsigned int start_col, Coord direction, unsigned int length) const
{
    std::string result;
    for (unsigned int i = 0; i < length; ++i)
    {
        int new_row = static_cast<int>(start_row) + i * direction.first;
        int new_col = static_cast<int>(start_col) + i * direction.second;
        if (!in_bounds(new_row, new_col))
        {
            break;
        }
        result += m_tiles[new_row][new_col];
    }
    return result;
}

bool TileMap::in_bounds(int row, int col) const
{
    return row >= 0 && row < static_cast<int>(m_rows) && col >= 0 && col < static_cast<int>(m_cols);
}
