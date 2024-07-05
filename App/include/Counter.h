#pragma once

#include <cstdint>

struct Counter{
    std::uint32_t correct_words = 0;
    std::uint32_t missed_words = 0;
    std::uint32_t word_pushed = 0;

    std::uint32_t getSum(){
        return correct_words + missed_words;
    }
};