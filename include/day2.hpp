#include "day.hpp"
#include <vector>

class Report
{
public:
    Report(std::string line);
    bool is_safe(bool dampen) const;

private:
    bool within_threshold(int difference) const;
    bool check_safety(std::vector<int> levels) const;
    std::vector<int> m_levels;
};

class Day2 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path &input_path) override;
    unsigned int get_day_number() const override { return 2; }
    std::string get_day_name() const override { return "Red-Nosed Reports"; }

private:
    std::vector<Report> parse_input(const std::filesystem::path &input_path);
    int part1(const std::vector<Report> &reports);
    int part2(const std::vector<Report> &reports);
};
