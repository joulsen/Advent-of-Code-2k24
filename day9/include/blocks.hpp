#ifndef AOC2024_DAY9_DISK_MAP_BLOCKS_HPP
#define AOC2024_DAY9_DISK_MAP_BLOCKS_HPP

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace DiskMap
{
class Blocks
{
public:
    Blocks(const std::string& input)
    {
        assert(input.size() / 2 <= static_cast<size_t>(std::numeric_limits<uint16_t>::max()) + 1);
        m_data.reserve(input.size() * 9);

        for (size_t i = 0; i < input.size(); ++i)
        {
            char c = input[i];
            if (c < '0' || c > '9') continue;  // Skip invalid characters (e.g. newline)

            uint8_t count = c - '0';
            uint16_t file_id = (i % 2 == 0) ? static_cast<uint16_t>(i / 2) : -1;
            for (unsigned int i = 0; i < count; ++i)
            {
                m_data.push_back(file_id);
            }
        }
    }

    uint64_t get_checksum() const
    {
        uint64_t checksum = 0;
        for (size_t i = 0; i < m_data.size(); ++i)
        {
            if (m_data[i] != static_cast<uint16_t>(-1))
            {
                checksum += static_cast<uint64_t>(i) * static_cast<uint64_t>(m_data[i]);
            }
        }
        return checksum;
    }

    const uint16_t& operator[](size_t index) const { return m_data[index]; }
    const bool free_at(size_t index) const { return m_data[index] == static_cast<uint16_t>(-1); }
    size_t size() const { return m_data.size(); }
    void swap(size_t index1, size_t index2) { std::swap(m_data[index1], m_data[index2]); }
    Blocks(const Blocks& other) = default;

private:
    std::vector<uint16_t> m_data;
};

void defragment_block_wise(Blocks& blocks)
{
    size_t free_index = 0;
    size_t data_index = blocks.size() - 1;

    while (true)
    {
        if (free_index > data_index) break;
        // Swap if free_index points to free and data_index points to data
        // Else, increment/decrement pointers accordingly
        if (blocks.free_at(free_index) && !blocks.free_at(data_index))
        {
            blocks.swap(free_index, data_index);
        }
        data_index += (blocks.free_at(data_index)) ? -1 : 0;
        free_index += (!blocks.free_at(free_index)) ? 1 : 0;
    }
}

}  // namespace DiskMap

#endif  // AOC2024_DAY9_DISK_MAP_BLOCKS_HPP