#pragma once
#include <chrono>
#include <random>

std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

int GetRandomNumber(int left_bound, int right_bound) {
    auto width = right_bound - left_bound + 1;
    return left_bound + static_cast<int>(rnd()) % width;
}

int GetRandomNumber(int bound) {
    return rnd() % bound;
}
