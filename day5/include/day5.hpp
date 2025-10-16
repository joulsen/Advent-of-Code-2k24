#ifndef AOC2024_DAY5_HPP
#define AOC2024_DAY5_HPP

#include "day.hpp"
#include "jobs.hpp"
#include "rules.hpp"

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