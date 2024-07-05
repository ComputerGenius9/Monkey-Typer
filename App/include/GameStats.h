#pragma once

#include <cstdint>

#include <SFML/System/Time.hpp>

struct GameStats
{
    std::uint32_t max_words = 0;
    sf::Time elapsed_time;
    std::uint32_t correct_words = 0;
    std::uint32_t missed_words = 0;
};