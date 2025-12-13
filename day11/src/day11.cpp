#include "day11.hpp"

#include <fstream>
#include <string>
#include <vector>

std::pair<std::string, std::string> Day11::run(const std::filesystem::path& input_path)
{
    std::vector<std::string> stones = parse_input(input_path);
    blink_cache cache;

    return {std::to_string(blink_list(stones, 25, cache)), std::to_string(blink_list(stones, 75, cache))};
}

std::vector<std::string> Day11::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::vector<std::string> stones;
    for (std::string stone; input_file >> stone;)
    {
        stones.push_back(stone);
    }
    input_file.close();
    return stones;
}

stone_t Day11::blink_single(std::string stone, blink_t blinks, blink_cache& cache) const
{
    if (blinks == 0) return 1;  // Base case: count the stone itself
    if (cache.count(stone) && cache[stone].count(blinks)) return cache[stone][blinks];

    stone_t stones_produced = 0;
    if (stone == "0")
    {
        stones_produced = blink_single("1", blinks - 1, cache);
    }
    else if (stone.size() % 2 == 0)
    {
        std::string stone_left = stone.substr(0, stone.size() / 2);
        std::string stone_right = stone.substr(stone.size() / 2);
        while (stone_right.size() > 1 && stone_right[0] == '0')
        {
            stone_right.erase(0, 1);
        }
        stones_produced += blink_single(stone_left, blinks - 1, cache);
        stones_produced += blink_single(stone_right, blinks - 1, cache);
    }
    else
    {
        stone_t new_stone = std::stoull(stone) * 2024;
        stones_produced = blink_single(std::to_string(new_stone), blinks - 1, cache);
    }

    cache[stone][blinks] = stones_produced;
    return stones_produced;
}

stone_t Day11::blink_list(const std::vector<std::string>& stones, blink_t blinks, blink_cache& cache) const
{
    stone_t total_stones = 0;
    for (const std::string& stone : stones)
    {
        total_stones += blink_single(stone, blinks, cache);
    }
    return total_stones;
}
