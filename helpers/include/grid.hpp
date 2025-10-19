#ifndef AOC2024_HELPERS_GRID_HPP
#define AOC2024_HELPERS_GRID_HPP

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
        if (!in_bounds(point.x, point.y)) throw std::out_of_range("Point is out of grid bounds");
        return m_data[point.y][point.x];
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
            if (in_bounds(neighbor.x, neighbor.y))
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
            if (in_bounds(neighbor.x, neighbor.y))
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
            if (!in_bounds(current.x, current.y)) break;
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
            if (!in_bounds(point.x, point.y)) continue;
            result += m_data[point.y][point.x];
        }
        return result;
    }

    bool in_bounds(int x, int y) const { return x >= 0 && x < static_cast<int>(m_cols) && y >= 0 && y < static_cast<int>(m_rows); }

private:
    std::vector<std::vector<char>> m_data;
    std::unordered_map<char, std::vector<Point>> m_char_positions;
    unsigned int m_rows;
    unsigned int m_cols;
};

#endif  // AOC2024_HELPERS_GRID_HPP