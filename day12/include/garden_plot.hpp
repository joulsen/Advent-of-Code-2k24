#ifndef AOC_2024_GARDEN_PLOT_HPP
#define AOC_2024_GARDEN_PLOT_HPP

#include <algorithm>
#include <iostream>
#include <unordered_set>

#include "grid.hpp"

class GardenPlot
{
public:
    GardenPlot(const Grid& grid, const Point& start_point) : m_grid(grid), m_char(grid.at(start_point))
    {
        m_points.reserve(grid.size());
        std::vector<Point> to_visit = {start_point};

        Point point;
        while (!to_visit.empty())
        {
            point = to_visit.back();
            to_visit.pop_back();
            if (m_points.count(point)) continue;
            m_points.insert(point);

            for (const Point& dir : {UP, DOWN, LEFT, RIGHT})
            {
                Point neighbor = point + dir;
                if (!grid.in_bounds(neighbor) || grid.at(neighbor) != m_char)
                {
                    m_fence.push_back(neighbor);
                }
                else if (m_grid.at(neighbor) == m_char && !m_points.count(neighbor))
                {
                    to_visit.push_back(neighbor);
                }
            }
        }
        std::sort(m_fence.begin(), m_fence.end());
    }

    uint16_t get_sides() const
    {
        std::cout << "Calculating sides for plot with char: " << m_char << std::endl;
        // Loop over each fence point. Travel cardinally keeping track of visits locally.
        std::vector<Point> to_visit = m_fence;
        std::unordered_set<Point> visited_horizontal;
        std::unordered_set<Point> visited_vertical;
        uint16_t sides = 0;
        std::vector<Point> looking_directions;

        while (!to_visit.empty())
        {
            if (visited_vertical.count(*to_visit.begin()))
            {
                looking_directions = {LEFT, RIGHT};
            }
            if (visited_horizontal.count(*to_visit.begin()))
            {
                looking_directions = {UP, DOWN};
            }
            else
            {
                looking_directions = {UP, DOWN, LEFT, RIGHT};
            }
            std::unordered_set<Point> fence_side_to_visit = {*to_visit.begin()};
            std::unordered_set<Point> fence_side_visited;
            while (!fence_side_to_visit.empty())
            {
                Point point = *fence_side_to_visit.begin();
                fence_side_to_visit.erase(point);
                // Only remove one occurrence of point from to_visit
                auto it = std::find(to_visit.begin(), to_visit.end(), point);
                if (it != to_visit.end())
                {
                    to_visit.erase(it);
                }
                fence_side_visited.insert(point);

                size_t i = 0;
                while (i < looking_directions.size())
                {
                    Point direction = looking_directions[i];
                    Point neighbor = point + direction;
                    i++;
                    if (std::find(to_visit.begin(), to_visit.end(), neighbor) != to_visit.end() && !fence_side_visited.count(neighbor))
                    {
                        fence_side_to_visit.insert(neighbor);
                        if (looking_directions.size() > 2)
                        {
                            if (direction == UP || direction == DOWN)
                            {
                                looking_directions = {UP, DOWN};
                            }
                            else
                            {
                                looking_directions = {LEFT, RIGHT};
                            }
                        }
                    }
                    if (direction == UP || direction == DOWN)
                    {
                        visited_vertical.insert(point);
                    }
                    else
                    {
                        visited_horizontal.insert(point);
                    }
                }
            }
            sides++;
        }
        return sides;
    }

    const std::unordered_set<Point>& get_points() const { return m_points; }
    uint16_t get_price_1() const { return static_cast<uint16_t>(m_points.size()) * static_cast<uint16_t>(m_fence.size()); }
    uint16_t get_price_2() const { return static_cast<uint16_t>(m_points.size()) * get_sides(); }

private:
    const Grid& m_grid;
    char m_char;
    std::unordered_set<Point> m_points;
    std::vector<Point> m_fence;
};

#endif  // AOC_2024_GARDEN_PLOT_HPP