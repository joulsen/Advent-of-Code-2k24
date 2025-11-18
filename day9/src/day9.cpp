#include "day9.hpp"

#include <fstream>
#include <string>
#include <vector>

#include "blocks.hpp"
#include "spans.hpp"

std::pair<std::string, std::string> Day9::run(const std::filesystem::path& input_path)
{
    DiskMap::Blocks blocks = parse_input(input_path);
    DiskMap::Blocks blocks_2(blocks);
    DiskMap::Spans spans(blocks_2);

    DiskMap::defragment_block_wise(blocks);
    DiskMap::defragment_span_wise(spans);

    return {std::to_string(blocks.get_checksum()), std::to_string(blocks_2.get_checksum())};
}

DiskMap::Blocks Day9::parse_input(const std::filesystem::path& input_path)
{
    std::ifstream input_file(input_path);
    std::string contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();
    return DiskMap::Blocks(contents);
}