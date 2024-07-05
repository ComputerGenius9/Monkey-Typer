#include "GenerateWord.h"

#include <random>

namespace Utils{

std::string generate_word(std::uint32_t max_length, std::uint32_t min_length)
{
    if (max_length == 0) {
        return "";
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> length_dist(min_length, max_length);
    std::uniform_int_distribution<> char_dist(0, 51);

    std::size_t word_length = length_dist(gen);

    static const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string word;
    word.reserve(word_length);
    for (std::size_t i = 0; i < word_length; ++i) {
        word += alphabet[char_dist(gen)];
    }

    return word;
}

}