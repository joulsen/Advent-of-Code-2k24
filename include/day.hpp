#ifndef AOC2024_DAY_HPP
#define AOC2024_DAY_HPP

#include <filesystem>

class Day
{
public:
    virtual ~Day() = default;
    virtual std::pair<std::string, std::string> run(const std::filesystem::path &input_path) = 0;
    virtual unsigned int get_day_number() const = 0;
    virtual std::string get_day_name() const = 0;
};

#endif // AOC2024_DAY_HPP