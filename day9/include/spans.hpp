#ifndef AOC2024_DAY9_DISK_MAP_SPANS_HPP
#define AOC2024_DAY9_DISK_MAP_SPANS_HPP

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

#include "blocks.hpp"

namespace DiskMap
{
struct Span
{
    uint16_t id;  // -1 for free span
    size_t start;
    uint8_t length;
    std::string to_string() const
    {
        std::ostringstream oss;
        oss << "Span{id=" << id << ", start=" << start << ", length=" << static_cast<int>(length) << "}";
        return oss.str();
    }
};

class Spans
{
public:
    Spans(Blocks& blocks) : m_blocks(blocks) {}

    void get_spans(std::vector<Span>& file_spans, std::vector<Span>& free_spans) const
    {
        size_t index = 0;
        Span current_span;
        while (index < m_blocks.size())
        {
            current_span.start = index;
            current_span.id = m_blocks[index];
            current_span.length = 0;
            while (index < m_blocks.size() && m_blocks[index] == current_span.id)
            {
                ++current_span.length;
                ++index;
            }
            if (current_span.id == static_cast<uint16_t>(-1))
            {
                free_spans.push_back(current_span);
            }
            else
            {
                file_spans.push_back(current_span);
            }
        }
    }

    bool fill(Span& from, Span& into)
    {
        if (from.length > into.length) return false;
        for (size_t i = 0; i < from.length; ++i)
        {
            m_blocks.swap(from.start + i, into.start + i);
        }
        from.start = into.start;
        into.start += from.length;
        into.length -= from.length;
        return true;
    }

private:
    Blocks& m_blocks;
};

void defragment_span_wise(Spans& spans)
{
    std::vector<Span> file_spans, free_spans;
    spans.get_spans(file_spans, free_spans);

    for (size_t i = file_spans.size(); i > 0; --i)
    {
        Span file_span = file_spans[i - 1];
        for (size_t j = 0; j < free_spans.size(); ++j)
        {
            if (free_spans[j].start >= file_span.start)
            {
                break;  // No more valid free spans
            }

            if (spans.fill(file_span, free_spans[j]))
            {
                break;
            }
        }
    }
}

}  // namespace DiskMap

#endif  // AOC2024_DAY9_DISK_MAP_SPANS_HPP
