#ifndef AOC2024_DAY6_GUARD_HPP
#define AOC2024_DAY6_GUARD_HPP

#include <set>
#include <thread>

#include "grid.hpp"
#include "point.hpp"

enum class PatrolResult
{
    OUT_OF_BOUNDS = 0,
    LOOP = 1
};

class Guard
{
public:
    Guard(Grid& grid, const Point& position) : m_grid(grid), m_position(position), m_direction{UP} {}

    std::pair<PatrolResult, std::set<Point>> patrol()
    {
        std::set<Point> visited_positions;
        std::set<std::pair<Point, Point>> visited_states;
        unsigned int step = 0;

        while (true)
        {
            ++step;
            if (peek() == '#')
            {
                rotate();
                continue;
            }

            if (visited_states.count({m_position, m_direction}) > 0)
            {
                return {PatrolResult::LOOP, visited_positions};
            }

            visited_positions.insert(m_position);
            visited_states.insert({m_position, m_direction});
            if (!move())
            {
                return {PatrolResult::OUT_OF_BOUNDS, visited_positions};
            }
        }
    }

    void set_position(const Point& position)
    {
        m_position = position;
        m_direction = UP;
        m_grid.set(m_position, get_movement_char());
    }

private:
    char peek() const
    {
        const Point next_pos = m_position + m_direction;
        if (!m_grid.in_bounds(next_pos))
        {
            return ' ';
        }
        return m_grid.at(m_position + m_direction);
    }
    void rotate()
    {
        if (m_direction == UP) m_direction = RIGHT;
        else if (m_direction == RIGHT)
            m_direction = DOWN;
        else if (m_direction == DOWN)
            m_direction = LEFT;
        else if (m_direction == LEFT)
            m_direction = UP;
    }
    bool move()
    {
        const Point next_pos = m_position + m_direction;
        if (!m_grid.in_bounds(next_pos))
        {
            return false;
        }
        m_position = m_position + m_direction;
        return true;
    }

    char get_movement_char() const
    {
        if (m_direction == UP) return '^';
        else if (m_direction == DOWN)
            return 'v';
        else if (m_direction == LEFT)
            return '<';
        else if (m_direction == RIGHT)
            return '>';
        return '?';
    }

    Grid& m_grid;
    Point m_position;
    Point m_direction;
};

#endif  // AOC2024_DAY6_GUARD_HPP