#include "day1.hpp"
#include <iostream>
#include <filesystem>

void usage(std::string program_name)
{
    std::cout << "Usage: " << program_name << " <action>\n";
    std::cout << "Actions:\n";
    std::cout << "  run <day> <input_file>     Run the solution with the specified input file\n";
    std::cout << "  list                       List available days\n";
}

Day1 day1;

void list()
{
    std::cout << "Available days:\n";
    std::cout << "Day " << day1.get_day_number() << ": " << day1.get_day_name() << "\n";
}

void run(int day, const std::filesystem::path &input_path)
{
    if (!std::filesystem::exists(input_path))
    {
        throw std::runtime_error("Input file does not exist");
    }
    auto execute_day = [&](int day) -> std::pair<std::string, std::string>
    {
        switch (day)
        {
        case 1:
            return day1.run(input_path);
        default:
            throw std::runtime_error("Day not implemented");
        }
    };
    auto results = execute_day(day);
    std::cout << "Day " << day << " Results:\n";
    std::cout << "Part 1: " << results.first << "\n";
    std::cout << "Part 2: " << results.second << "\n";
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        usage(argv[0]);
        return 1;
    }
    std::string action = argv[1];
    if (action == "list")
    {
        list();
        return 0;
    }
    if (action == "run")
    {
        if (argc != 4)
        {
            usage(argv[0]);
            return 1;
        }
        int day = std::stoi(argv[2]);
        std::filesystem::path input_path = argv[3];
        run(day, input_path);
        return 0;
    }
    else
    {
        usage(argv[0]);
        return 1;
    }
}
