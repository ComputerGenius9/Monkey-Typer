#pragma once

#include <random>

namespace Utils {

template<typename Iter, typename RandomGenerator>
Iter select_random(Iter start, Iter end, RandomGenerator &g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_random(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_random(start, end, gen);
}

}