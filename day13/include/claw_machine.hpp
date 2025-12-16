#ifndef AOC_2024_CLAW_MACHINE_HPP
#define AOC_2024_CLAW_MACHINE_HPP

#include <cassert>
#include <cstdint>
#include <optional>
#include <utility>

using IntPair = std::pair<int64_t, int64_t>;

class ClawMachine
{
public:
    ClawMachine(IntPair a_button, IntPair b_button, IntPair prize_position)
        : m_a_button(a_button),
          m_b_button(b_button),
          m_prize_position(prize_position)
    {
    }

    std::optional<int64_t> get_cost(std::pair<int64_t, int64_t> prize_offset = {0, 0}) const
    {
        int64_t d = get_determinant();
        if (d == 0) return std::nullopt;
        int64_t px = m_prize_position.first + prize_offset.first;
        int64_t py = m_prize_position.second + prize_offset.second;

        int64_t a = (px * m_b_button.second - py * m_b_button.first);
        int64_t b = (m_a_button.first * py - m_a_button.second * px);

        if (a % d != 0 || b % d != 0) return std::nullopt;
        a /= d;
        b /= d;
        if (a < 0 || b < 0) return std::nullopt;

        return 3 * a + b;
    }

private:
    int64_t get_determinant() const { return m_a_button.first * m_b_button.second - m_a_button.second * m_b_button.first; }

    IntPair m_a_button;
    IntPair m_b_button;
    IntPair m_prize_position;
};

#endif  // AOC_2024_CLAW_MACHINE_HPP