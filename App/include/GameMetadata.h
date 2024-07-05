#pragma once

#include <set>
#include <deque>
#include <cstdint>
#include <map>
#include <stack>

struct GameMetadata{
    //Stack for unique words
    std::stack<std::string> nonvisible_words;
    std::map<std::uint32_t,std::deque<sf::Text>> visible_words;
};