#ifndef AOC2024_HELPERS_GRID_HPP
#define AOC2024_HELPERS_GRID_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "point.hpp"

class Grid
{
public:
    Grid(const std::vector<std::string>& input)
    {
        if (input.empty()) throw std::invalid_argument("Input vector is empty");
        m_rows = input.size();
        m_cols = input[0].size();
        m_data.resize(m_rows, std::vector<char>(m_cols));
        for (unsigned int r = 0; r < m_rows; ++r)
        {
            if (input[r].size() != m_cols) throw std::invalid_argument("All rows must have the same number of columns");
            for (unsigned int c = 0; c < m_cols; ++c)
            {
                char tile = input[r][c];
                m_data[r][c] = tile;
                m_char_positions[tile].emplace_back(Point{static_cast<int>(c), static_cast<int>(r)});
            }
        }
    }

    Grid(const std::string& input)
    {
        if (input.empty()) throw std::invalid_argument("Input string is empty");
        std::vector<std::string> lines;
        std::istringstream iss(input);
        std::string line;
        while (std::getline(iss, line))
        {
            lines.push_back(line);
        }
        *this = Grid(lines);
    }

    const char& at(const Point& point) const
    {
        if (!in_bounds(point))
        {
            throw std::out_of_range("Point is out of grid bounds");
        }
        return m_data[point.y][point.x];
    }

    bool set(const Point& point, char c)
    {
        if (!in_bounds(point)) return false;
        char& current_char = m_data[point.y][point.x];
        current_char = c;
        return true;
    }

    void rebuild_char_positions()
    {
        m_char_positions.clear();
        for (unsigned int r = 0; r < m_rows; ++r)
        {
            for (unsigned int c = 0; c < m_cols; ++c)
            {
                char tile = m_data[r][c];
                m_char_positions[tile].emplace_back(Point{static_cast<int>(c), static_cast<int>(r)});
            }
        }
    }

    const std::vector<Point>& get_points_by_char(char c) const
    {
        static const std::vector<Point> empty;
        auto it = m_char_positions.find(c);
        if (it != m_char_positions.end())
        {
            return it->second;
        }
        return empty;
    }

    std::vector<Point> get_neighbors(const Point& point) const
    {
        std::vector<Point> neighbors;
        for (const Point& dir : {UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT})
        {
            Point neighbor = point + dir;
            if (in_bounds(neighbor))
            {
                neighbors.push_back(neighbor);
            }
        }
        return neighbors;
    }

    std::vector<Point> get_neighbors_masked(const Point& point, const std::vector<Point>& mask) const
    {
        std::vector<Point> neighbors;
        for (const Point& dir : mask)
        {
            Point neighbor = point + dir;
            if (in_bounds(neighbor))
            {
                neighbors.push_back(neighbor);
            }
        }
        return neighbors;
    }

    std::vector<Point> get_points_in_direction(const Point& start, const Point& direction, unsigned int distance) const
    {
        std::vector<Point> points;
        Point current = start;
        for (unsigned int i = 0; i < distance; ++i)
        {
            if (!in_bounds(current)) break;
            points.push_back(current);
            current = current + direction;
        }
        return points;
    }

    std::string points_to_string(const std::vector<Point>& points) const
    {
        std::string result;
        for (const auto& point : points)
        {
            if (!in_bounds(point)) continue;
            result += m_data[point.y][point.x];
        }
        return result;
    }

    bool in_bounds(const Point& point) const { return in_bounds(point.x, point.y); }
    bool in_bounds(int x, int y) const { return x >= 0 && x < static_cast<int>(m_cols) && y >= 0 && y < static_cast<int>(m_rows); }

    void to_file(const std::filesystem::path& output_path) const
    {
        std::ofstream output_file(output_path);
        for (const auto& row : m_data)
        {
            for (const auto& cell : row)
            {
                output_file << cell;
            }
            output_file << '\n';
        }
        output_file.close();
    }

    unsigned int rows() const { return m_rows; }
    unsigned int cols() const { return m_cols; }
    unsigned int size() const { return m_rows * m_cols; }
    unsigned int max_dimension() const { return std::max(m_rows, m_cols); }
    const std::unordered_map<char, std::vector<Point>>& char_positions() const { return m_char_positions; }

private:
    std::vector<std::vector<char>> m_data;
    std::unordered_map<char, std::vector<Point>> m_char_positions;
    unsigned int m_rows;
    unsigned int m_cols;
};

#endif  // AOC2024_HELPERS_GRID_HPP