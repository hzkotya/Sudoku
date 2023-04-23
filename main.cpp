#pragma once
#include <iostream>
#include <vector>
#include "Sudoku.h"

int main() {
    auto s = Sudoku();
    s.printans();
    s.print();
    while (true) {
       s.Fill();
    }
    return 0;
}