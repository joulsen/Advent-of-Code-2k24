#ifndef AOC2024_DAY5_HPP
#define AOC2024_DAY5_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "day.hpp"

class Rules
{
public:
    Rules(std::string rules);
    inline std::vector<int> get(int page_numbers) const;

private:
    std::unordered_map<int, std::vector<int>> m_rules;
};

class Job
{
public:
    Job(std::vector<int> pages) : m_pages(pages) {}
    bool has_correct_order(const Rules& rules) const;
    int get_middle_page() const { return m_pages[m_pages.size() / 2]; }
    bool order(const Rules& rules);

private:
    std::vector<int> m_pages;
    bool has_page_before_index(size_t start_index, int page) const;
    bool index_satisfies_rules(size_t index, const Rules& rules) const;
};

class Jobs
{
public:
    Jobs(std::string jobs);
    Jobs(std::vector<Job> jobs) : m_jobs(jobs) {}
    std::pair<Jobs, Jobs> get_ordered_and_unordered_jobs(const Rules& rules) const;
    int sum_middle_pages() const;
    void order_jobs(const Rules& rules);

private:
    std::vector<Job> m_jobs;
};

class Day5 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 5; }
    std::string get_day_name() const override { return "Print Queue"; }

private:
    std::pair<Rules, Jobs> parse_input(const std::filesystem::path& input_path);
};

REGISTER_DAY(Day5, 5)

#endif  // AOC2024_DAY5_HPP