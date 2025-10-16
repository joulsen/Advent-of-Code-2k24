#ifndef AOC2024_DAY5_JOB_HPP
#define AOC2024_DAY5_JOB_HPP

#include <string>
#include <vector>

#include "day5/rules.hpp"

class Job
{
public:
    Job(std::vector<int> pages) : m_pages(pages) {}
    bool has_correct_order(const Rules& rules) const
    {
        for (size_t i = 0; i < m_pages.size(); ++i)
        {
            if (!index_satisfies_rules(i, rules))
            {
                return false;
            }
        }
        return true;
    }

    int get_middle_page() const { return m_pages[m_pages.size() / 2]; }

    bool order(const Rules& rules)
    {
        // Like above, but move a page to the left if it does not satisfy the rules
        for (size_t i = 0; i < m_pages.size(); ++i)
        {
            if (!index_satisfies_rules(i, rules))
            {
                if (i == 0)
                {
                    throw std::runtime_error("Cannot order job, first page violates rules");
                }
                std::swap(m_pages[i], m_pages[i - 1]);
                return true;
            }
        }
        return false;
    }

private:
    bool has_page_before_index(size_t index, int page) const
    {
        for (size_t i = 0; i < std::min(index, m_pages.size()); ++i)
        {
            if (m_pages[i] == page)
            {
                return true;
            }
        }
        return false;
    }

    bool index_satisfies_rules(size_t index, const Rules& rules) const
    {
        for (int rule : rules.get(m_pages[index]))
        {
            if (has_page_before_index(index, rule))
            {
                return false;
            }
        }
        return true;
    }

    std::vector<int> m_pages;
};

#endif  // AOC2024_DAY5_JOB_HPP