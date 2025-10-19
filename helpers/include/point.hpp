#ifndef AOC2024_HELPERS_POINT_HPP
#define AOC2024_HELPERS_POINT_HPP

#include <array>
#include <string>

struct Point
{
    int x;
    int y;

    constexpr Point operator+(const Point& other) const { return {x + other.x, y + other.y}; }
    constexpr Point operator-(const Point& other) const { return {x - other.x, y - other.y}; }
    constexpr Point operator*(int scalar) const { return {x * scalar, y * scalar}; }
    constexpr bool operator==(const Point& other) const { return x == other.x && y == other.y; }
    std::string to_string() const { return "(" + std::to_string(x) + ", " + std::to_string(y) + ")"; }
};

// Direction constants
constexpr Point UP{0, -1};
constexpr Point DOWN{0, 1};
constexpr Point LEFT{-1, 0};
constexpr Point RIGHT{1, 0};
constexpr Point UP_LEFT{-1, -1};
constexpr Point UP_RIGHT{1, -1};
constexpr Point DOWN_LEFT{-1, 1};
constexpr Point DOWN_RIGHT{1, 1};

constexpr std::array<Point, 4> DIRECTIONS_CARDINAL{UP, DOWN, LEFT, RIGHT};
constexpr std::array<Point, 4> DIRECTIONS_DIAGONAL{UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT};
constexpr std::array<Point, 8> DIRECTIONS_ALL{UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT};

#endif  // AOC2024_HELPERS_POINT_HPP