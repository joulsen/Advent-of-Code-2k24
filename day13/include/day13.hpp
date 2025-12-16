#ifndef AOC2024_DAY13_HPP
#define AOC2024_DAY13_HPP

#include <string>
#include <vector>

#include "claw_machine.hpp"
#include "day.hpp"

class Day13 : public Day
{
public:
    std::pair<std::string, std::string> run(const std::filesystem::path& input_path) override;
    unsigned int get_day_number() const override { return 13; }
    std::string get_day_name() const override { return "Claw Contraption"; }

private:
    std::vector<ClawMachine> parse_input(const std::filesystem::path& input_path);
};

REGISTER_DAY(Day13, 13)
#endif  // AOC2024_DAY13_HPP