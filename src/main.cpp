#include <chrono>
#include <filesystem>
#include <iostream>

#include "day.hpp"

void usage(std::string program_name)
{
    std::cout << "Usage: " << program_name << " <action>\n";
    std::cout << "Actions:\n";
    std::cout << "  run <day> <input_file>     Run the solution with the specified input file\n";
    std::cout << "  list                       List available days\n";
}

void list()
{
    std::cout << "Available days:\n";
    auto& factory = DayFactory::instance();
    auto all_days = factory.get_all_days();

    for (const auto& [day_num, creator] : all_days)
    {
        auto day_instance = creator();
        std::cout << "Day " << day_instance->get_day_number() << ": " << day_instance->get_day_name() << "\n";
    }
}

void run(int day, const std::filesystem::path& input_path)
{
    if (!std::filesystem::exists(input_path))
    {
        throw std::runtime_error("Input file does not exist");
    }

    auto& factory = DayFactory::instance();
    auto day_instance = factory.create_day(day);

    if (!day_instance)
    {
        throw std::runtime_error("Day " + std::to_string(day) + " not implemented");
    }

    try
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto results = day_instance->run(input_path);
        auto duration = std::chrono::high_resolution_clock::now() - now;
        double ms = std::chrono::duration<double, std::milli>(duration).count();
        std::cout << "Day " << day << " Results:\n";
        std::cout << "Part 1: " << results.first << "\n";
        std::cout << "Part 2: " << results.second << "\n";
        std::cout << "Duration: " << ms << " ms\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error running day " << day << ": " << e.what() << "\n";
        throw;
    }
}

int main(int argc, char* argv[])
{
    try
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
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
