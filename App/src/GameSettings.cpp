#include "../include/GameSettings.h"
#include "../../Utils/SelectRandom.h"

GameSettings::GameSettings(
    std::int32_t deadline,
    std::int32_t words,
    std::int32_t speed,
    std::int32_t max_word_length,
    std::int32_t window_width,
    std::int32_t window_height)
    : deadline_(1,100,deadline)
    , words_(10,10000,words)
    , speed_(1,8,speed)
    , max_word_length_(2,15,max_word_length)
    , window_width_(500,1920,window_width)
    , window_height_(500,1080,window_height)
{

}

GameSettings::GameSettings(std::int32_t window_width, std::int32_t window_height)
    : deadline_(1,100,10)
    , words_(10,10000,100)
    , speed_(1,8,4)
    , max_word_length_(2,15,10)
    , window_width_(500,1920,window_width)
    , window_height_(500,1080,window_height)
{

}

GameParam &GameSettings::getDeadlineParam()
{
    return deadline_;
}

GameParam &GameSettings::getWordsParam()
{
    return words_;
}

GameParam &GameSettings::getSpeedParam()
{
    return speed_;
}

GameParam &GameSettings::getMaxWordLengthParam()
{
    return max_word_length_;
}

GameParam &GameSettings::getScreenHeightParam()
{
    return window_height_;
}

GameParam &GameSettings::getScreenWidthParam()
{
    return window_width_;
}

const sf::Font &GameSettings::getFont() const
{
    return font_param_.current_font;
}

std::string GameSettings::getFontName() const
{
    return font_param_.current_font_name;
}

void GameSettings::setFonts(const std::vector<std::pair<std::string, sf::Font>> &fonts)
{
    for(const auto &[name,font] : fonts){
        font_param_.fonts[name] = font;
    }
    font_param_.current_font_name = fonts.begin()->first;
    font_param_.current_font = fonts.begin()->second;
}


void GameSettings::changeFont(bool up)
{
    auto it_current = font_param_.fonts.find(font_param_.current_font_name);
    if(up){
        if(font_param_.fonts.end() == std::next(it_current)){
            font_param_.current_font_name = font_param_.fonts.begin()->first;
            font_param_.current_font = font_param_.fonts.begin()->second;
        }else{
            it_current++;
            font_param_.current_font_name = it_current->first;
            font_param_.current_font = it_current->second;
        }
    }else{
        if(font_param_.fonts.begin() == it_current){
            font_param_.current_font_name = std::prev(font_param_.fonts.end())->first;
            font_param_.current_font = std::prev(font_param_.fonts.end())->second;
        }else{
            it_current--;
            font_param_.current_font_name = it_current->first;
            font_param_.current_font = it_current->second;
        }
    }
}


