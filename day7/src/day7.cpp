#include "day7.hpp"

#include <fstream>
#include <string>
#include <vector>

#include "equation.hpp"

std::pair<std::string, std::string> Day7::run(const std::filesystem::path& input_path)
{
    std::vector<Equation> equations = parse_input(input_path);
    unsigned long long result_part1 = part1(equations);
    unsigned long long result_part2 = part2(equations);
    return {std::to_string(result_part1), std::to_string(result_part2)};
}

std::vector<Equation> Day7::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::string line;
    std::vector<Equation> equations;
    while (std::getline(input_file, line))
    {
        if (!line.empty())
        {
            equations.emplace_back(Equation(line));
        }
    }
    input_file.close();
    return equations;
}

unsigned long long Day7::part1(const std::vector<Equation>& equations)
{
    unsigned long long calibration_results = 0;
    for (const auto& equation : equations)
    {
        if (equation.is_solvable({Equation::add, Equation::multiply}))
        {
            calibration_results += equation.get_result();
        }
    }
    return calibration_results;
}

unsigned long long Day7::part2(const std::vector<Equation>& equations)
{
    unsigned long long calibration_result = 0;
    for (const auto& equation : equations)
    {
        if (equation.is_solvable({Equation::add, Equation::multiply, Equation::concatenate}))
        {
            calibration_result += equation.get_result();
        }
    }
    return calibration_result;
}
