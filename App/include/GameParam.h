#pragma once

#include <cstdint>

class GameParam{

public:
    GameParam(std::int32_t p_min_value, std::int32_t p_max_value, std::int32_t p_initial);

    void increase();
    void decrease();
    bool isMin() const;
    bool isMax() const;
    std::int32_t getValue() const;
    std::int32_t getMinValue() const;
    void setValue(std::int32_t value);

private:
    std::int32_t current_;
    std::int32_t min_value_;
    std::int32_t max_value_;
};