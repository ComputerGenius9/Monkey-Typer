#pragma once

#include <cstdint>
#include <string>

struct GameRecord
{
    std::string assigned_name;
    std::uint32_t max_words{};
    std::uint32_t missed_words{};
    std::uint32_t correct_words{};
    std::uint32_t elapsed_time{};
};