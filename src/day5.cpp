#include "day5.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

Rules::Rules(std::string rules)
{
    // Rulestring example: "47|53\n97|13\n97|61\n..."
    std::stringstream ss(rules);
    int page1, page2;
    char separator;
    for (std::string line; std::getline(ss, line);)
    {
        std::stringstream line_ss(line);
        if (!(line_ss >> page1 >> separator >> page2))
        {
            throw std::runtime_error("Invalid rules line: " + line);
        }
        m_rules[page1].push_back(page2);
    }
}

std::vector<int> Rules::get(int page_numbers) const
{
    auto it = m_rules.find(page_numbers);
    if (it != m_rules.end())
    {
        return it->second;
    }
    return {};
}

bool Job::has_page_before_index(size_t index, int page) const
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

bool Job::index_satisfies_rules(size_t index, const Rules& rules) const
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

bool Job::has_correct_order(const Rules& rules) const
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

bool Job::order(const Rules& rules)
{
    // Like above, but move a page to the left if it does not satisfy the rules
    for (size_t i = 0; i < m_pages.size(); ++i)
    {
        if (!index_satisfies_rules(i, rules))
        {
            if (i == 0)
            {
                throw std::runtime_error("Cannot order job: first page violates rules");
            }
            std::swap(m_pages[i], m_pages[i - 1]);
            return true;
        }
    }
    return false;
}

Jobs::Jobs(std::string jobs)
{
    // Jobs string example: "75,47,61,53,29\n97,61,53,29,13\n...""
    std::stringstream ss(jobs);
    int page;
    for (std::string line; std::getline(ss, line);)
    {
        std::stringstream line_ss(line);
        std::vector<int> job;
        while (line_ss >> page)
        {
            job.push_back(page);
            if (line_ss.peek() == ',')
            {
                line_ss.ignore();
            }
        }
        if (job.size() % 2 == 0)
        {
            throw std::runtime_error("Job must have an odd number of pages: " + line);
        }
        m_jobs.push_back(job);
    }
}

std::pair<Jobs, Jobs> Jobs::get_ordered_and_unordered_jobs(const Rules& rules) const
{
    std::vector<Job> ordered_jobs;
    std::vector<Job> unordered_jobs;
    for (const Job& job : m_jobs)
    {
        if (job.has_correct_order(rules))
        {
            ordered_jobs.push_back(job);
        }
        else
        {
            unordered_jobs.push_back(job);
        }
    }
    return {ordered_jobs, unordered_jobs};
}

int Jobs::sum_middle_pages() const
{
    int sum = 0;
    for (const Job& job : m_jobs)
    {
        sum += job.get_middle_page();
    }
    return sum;
}

void Jobs::order_jobs(const Rules& rules)
{
    for (Job& job : m_jobs)
    {
        while (job.order(rules));
    }
}

std::pair<std::string, std::string> Day5::run(const std::filesystem::path& input_path)
{
    auto [rules, jobs] = parse_input(input_path);
    auto [ordered_jobs, unordered_jobs] = jobs.get_ordered_and_unordered_jobs(rules);
    unordered_jobs.order_jobs(rules);
    int part1 = Jobs(ordered_jobs).sum_middle_pages();
    int part2 = Jobs(unordered_jobs).sum_middle_pages();
    return {std::to_string(part1), std::to_string(part2)};
}

std::pair<Rules, Jobs> Day5::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::string contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();

    size_t separator_pos = contents.find("\n\n");
    if (separator_pos == std::string::npos)
    {
        throw std::runtime_error("Invalid input format: missing separator between rules and jobs");
    }

    std::string rules_str = contents.substr(0, separator_pos);
    std::string jobs_str = contents.substr(separator_pos + 2);  // Skip the two newlines

    return {Rules(rules_str), Jobs(jobs_str)};
}
