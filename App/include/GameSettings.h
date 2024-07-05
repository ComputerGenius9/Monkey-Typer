#pragma once

#include "GameParam.h"

#include <cstdint>

#include <SFML/Graphics/Font.hpp>

struct FontParam{
    std::map<std::string,sf::Font> fonts;
    sf::Font current_font;
    std::string current_font_name;
};

class GameSettings {
public:
    GameSettings(
        std::int32_t deadline,
        std::int32_t words,
        std::int32_t speed,
        std::int32_t max_word_length,
        std::int32_t window_width,
        std::int32_t window_height);

    GameSettings(std::int32_t window_width, std::int32_t window_height);

    GameParam &getDeadlineParam();
    GameParam &getWordsParam();
    GameParam &getSpeedParam();
    GameParam &getMaxWordLengthParam();
    GameParam &getScreenWidthParam();
    GameParam &getScreenHeightParam();

    void setFonts(const std::vector<std::pair<std::string, sf::Font>> &fonts);

    void changeFont(bool up);
    const sf::Font &getFont() const;
    std::string getFontName() const;

private:
    GameParam deadline_;
    GameParam words_;
    GameParam speed_;
    GameParam max_word_length_;
    GameParam window_width_;
    GameParam window_height_;
    FontParam font_param_;
};
