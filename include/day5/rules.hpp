#ifndef AOC2024_DAY5_RULES_HPP
#define AOC2024_DAY5_RULES_HPP

#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class Rules
{
public:
    Rules(std::string rules)
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

    inline std::vector<int> get(int page_numbers) const
    {
        auto it = m_rules.find(page_numbers);
        if (it != m_rules.end())
        {
            return it->second;
        }
        return {};
    }

private:
    std::unordered_map<int, std::vector<int>> m_rules;
};

#endif  // AOC2024_DAY5_RULES_HPP