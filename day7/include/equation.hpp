#ifndef AOC2024_DAY7_EQUATION_HPP
#define AOC2024_DAY7_EQUATION_HPP

#include <algorithm>
#include <deque>
#include <functional>
#include <string>
#include <vector>

using EquationOperator = std::function<long long(unsigned long long, unsigned long long)>;

class Equation
{
public:
    Equation(unsigned long long result, std::vector<unsigned long long> values) : m_result(result), m_values(std::move(values)) {}

    Equation(std::string equation_str)
    {
        // Example: "3267: 81 40 27"
        auto colon_pos = equation_str.find(':');
        m_result = std::stoull(equation_str.substr(0, colon_pos));
        std::string values_str = equation_str.substr(colon_pos + 1);
        size_t pos = 0;
        while (pos < values_str.length())
        {
            size_t next_space = values_str.find(' ', pos);
            if (next_space == std::string::npos) next_space = values_str.length();
            std::string value = values_str.substr(pos, next_space - pos);
            if (!value.empty()) m_values.push_back(std::stoull(value));
            pos = next_space + 1;
        }
        *this = Equation(m_result, m_values);
    }

    unsigned long long get_result() const { return m_result; }

    inline static long long add(unsigned long long a, unsigned long long b) { return a + b; }
    inline static long long multiply(unsigned long long a, unsigned long long b) { return a * b; }
    inline static long long concatenate(unsigned long long a, unsigned long long b)
    {
        std::string concatenated = std::to_string(a) + std::to_string(b);
        return std::stoull(concatenated);
    }

    bool is_solvable(const std::vector<EquationOperator>& operators) const
    {
        std::deque<unsigned long long> scratchboard({m_values.front()});
        size_t scratchboard_iteration_size;
        for (size_t i = 1; i < m_values.size(); ++i)
        {
            scratchboard_iteration_size = scratchboard.size();
            for (size_t j = 0; j < scratchboard_iteration_size; ++j)
            {
                unsigned long long value = scratchboard.front();
                scratchboard.pop_front();

                for (const auto& op : operators)
                {
                    unsigned long long result = op(value, m_values[i]);
                    if (result <= m_result)
                    {
                        scratchboard.push_back(result);
                    }
                }
            }
        }

        const auto comparator = [this](unsigned long long value) { return value == m_result; };
        return std::any_of(scratchboard.begin(), scratchboard.end(), comparator);
    }

private:
    unsigned long long m_result;
    std::vector<unsigned long long> m_values;
};

#endif  // AOC2024_DAY7_EQUATION_HPP
