#include "../include/GameParam.h"

GameParam::GameParam(std::int32_t min_value, std::int32_t max_value, std::int32_t p_initial)
        : min_value_(min_value)
        , max_value_(max_value)
        , current_(p_initial)
{

}

void GameParam::increase()
{
    if(current_ < max_value_){
        current_++;
    }
}

void GameParam::decrease()
{
    if(current_ > min_value_){
        current_--;
    }
}

bool GameParam::isMin() const
{
    return current_ == min_value_;
}

bool GameParam::isMax() const
{
    return current_ == max_value_;
}

std::int32_t GameParam::getValue() const
{
    return current_;
}

std::int32_t GameParam::getMinValue() const
{
    return min_value_;
}

void GameParam::setValue(std::int32_t value)
{
    current_ = value;
}

