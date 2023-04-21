//
// Created by georg on 22.04.2023.
//

#ifndef PROGRAM_RANDOM_H
#define PROGRAM_RANDOM_H

#include <chrono>
#include <random>

std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

inline unsigned int GetRandomNumber(unsigned int left_bound, unsigned int right_bound) {
    auto width = right_bound - left_bound + 1;
    return left_bound + rnd() % width;
}

inline unsigned int GetRandomNumber(unsigned int bound) {
    return rnd() % bound;
}


#endif //PROGRAM_RANDOM_H
