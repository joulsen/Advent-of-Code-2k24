#ifndef AOC_2024_ROBOT_HPP
#define AOC_2024_ROBOT_HPP

#include <cstdint>
#include <iostream>
#include <numeric>
#include <optional>

#include "point.hpp"

constexpr int32_t MAP_WIDTH = 101;
constexpr int32_t MAP_HEIGHT = 103;

class Robot
{
public:
    Robot(Point position, Point velocity, int32_t map_width = MAP_WIDTH, int32_t map_height = MAP_HEIGHT)
        : m_position(position),
          m_velocity(velocity),
          m_map_width(map_width),
          m_map_height(map_height)
    {
    }

    void move(int32_t time)
    {
        int32_t new_x = (m_position.x + m_velocity.x * time) % m_map_width;
        int32_t new_y = (m_position.y + m_velocity.y * time) % m_map_height;
        if (new_x < 0) new_x += m_map_width;
        if (new_y < 0) new_y += m_map_height;
        m_position.x = new_x;
        m_position.y = new_y;
    }

    Point get_position() const { return m_position; }
    int32_t get_map_width() const { return m_map_width; }
    int32_t get_map_height() const { return m_map_height; }

    std::optional<int> get_quadrant() const
    {
        if (m_position.x < m_map_width / 2 && m_position.y < m_map_height / 2) return 0;
        if (m_position.x > m_map_width / 2 && m_position.y < m_map_height / 2) return 1;
        if (m_position.x < m_map_width / 2 && m_position.y > m_map_height / 2) return 2;
        if (m_position.x > m_map_width / 2 && m_position.y > m_map_height / 2) return 3;
        return std::nullopt;
    }

private:
    Point m_position;
    Point m_velocity;
    int32_t m_map_width;
    int32_t m_map_height;
};

class RobotContainer
{
public:
    RobotContainer(const std::vector<Robot>& robots) : m_robots(robots), m_initial_robots(robots) { calculate_robot_count(); }

    void reset(int32_t time = 0)
    {
        m_robots = m_initial_robots;
        move_all(time);
        calculate_robot_count();
    }

    void move_all(int32_t time)
    {
        for (auto& robot : m_robots)
        {
            robot.move(time);
        }
        calculate_robot_count();
    }

    uint64_t get_safety_factor() const
    {
        std::vector<int> quadrants{0, 0, 0, 0};
        for (const auto& robot : m_robots)
        {
            std::optional<int> quadrant = robot.get_quadrant();
            if (quadrant)
            {
                quadrants[*quadrant]++;
            }
        }
        return static_cast<uint64_t>(quadrants[0]) * quadrants[1] * quadrants[2] * quadrants[3];
    }

    int32_t get_lcm() const { return std::lcm(m_robots[0].get_map_width(), m_robots[0].get_map_height()); }

    uint64_t get_clustering_score() const
    {
        uint64_t clustered_robots = 0;
        for (const auto& robot : m_robots)
        {
            Point pos = robot.get_position();
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    if (dx == 0 && dy == 0) continue;
                    Point neighbor_pos{pos.x + dx, pos.y + dy};
                    if (m_robot_count.count(neighbor_pos) > 0)
                    {
                        clustered_robots++;
                    }
                }
            }
        }
        return clustered_robots;
    }

    void print() const
    {
        for (int32_t y = 0; y < MAP_HEIGHT; ++y)
        {
            for (int32_t x = 0; x < MAP_WIDTH; ++x)
            {
                std::cout << (m_robot_count.count(Point{x, y}) ? std::to_string(m_robot_count.at(Point{x, y})) : ".");
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    const std::vector<Robot>& get_robots() const { return m_robots; }
    std::vector<Robot>& get_robots() { return m_robots; }

private:
    void calculate_robot_count()
    {
        m_robot_count.clear();
        for (const auto& robot : m_robots)
        {
            m_robot_count[robot.get_position()]++;
        }
    }

    std::vector<Robot> m_robots;
    std::vector<Robot> m_initial_robots;
    std::unordered_map<Point, int> m_robot_count;
};

#endif  // AOC_2024_ROBOT_HPP