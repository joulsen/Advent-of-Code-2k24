#ifndef AOC2024_DAY2_REPORT_HPP
#define AOC2024_DAY2_REPORT_HPP

#include <sstream>
#include <string>
#include <vector>

class Report
{
public:
    Report(std::string line)
    {
        std::istringstream iss(line);
        int value;
        while (iss >> value)
        {
            m_levels.push_back(value);
        }
    }

    bool is_safe(bool dampen) const
    {
        if (!dampen)
        {
            return check_safety(m_levels);
        }

        for (size_t i = 0; i < m_levels.size(); ++i)
        {
            std::vector<int> levels_missing_i;
            levels_missing_i.reserve(m_levels.size() - 1);
            for (size_t j = 0; j < m_levels.size(); ++j)
            {
                if (j != i)
                {
                    levels_missing_i.push_back(m_levels[j]);
                }
            }
            if (check_safety(levels_missing_i))
            {
                return true;
            }
        }
        return false;
    }

private:
    bool within_threshold(int difference) const { return (1 <= std::abs(difference) && std::abs(difference) <= 3); }

    bool check_safety(std::vector<int> levels) const
    {
        bool increasing = (levels[1] > levels[0]);
        for (size_t i = 1; i < levels.size(); ++i)
        {
            bool monotonic = increasing ? (levels[i] > levels[i - 1]) : (levels[i] < levels[i - 1]);
            int difference = std::abs(levels[i] - levels[i - 1]);
            bool threshold_ok = (1 <= difference && difference <= 3);
            if (!monotonic || !threshold_ok)
            {
                return false;
            }
        }
        return true;
    }

    std::vector<int> m_levels;
};

#endif  // AOC2024_DAY2_REPORT_HPP