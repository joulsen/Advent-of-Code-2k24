#ifndef AOC2024_DAY5_JOBS_HPP
#define AOC2024_DAY5_JOBS_HPP

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "day5/job.hpp"

class Jobs
{
public:
    Jobs(std::vector<Job> jobs) : m_jobs(jobs) {}
    Jobs(std::string jobs)
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

    std::pair<Jobs, Jobs> get_ordered_and_unordered_jobs(const Rules& rules) const
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

    int sum_middle_pages() const
    {
        int sum = 0;
        for (const Job& job : m_jobs)
        {
            sum += job.get_middle_page();
        }
        return sum;
    }

    void order_jobs(const Rules& rules)
    {
        for (Job& job : m_jobs)
        {
            while (job.order(rules));
        }
    }

private:
    std::vector<Job> m_jobs;
};

#endif  // AOC2024_DAY5_JOBS_HPP