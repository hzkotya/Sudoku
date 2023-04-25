#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <cassert>
#include <array>

class SudokuValidator {

public:
    static constexpr const int Size = 3;
    static constexpr const int BoxSize = 9;
    bool IsUniqueSolution = true;
    bool IsAnsFound = false;

    std::array <int, BoxSize> Counter{}, RowsBitmasks{}, ColumnsBitmasks{}, BoxesBitmasks{};
    std::vector<std::vector<int>> Sudoku;
    std::vector<std::vector<int>> Author_Solution;

    explicit SudokuValidator(const std::vector<std::vector<int>> &grid, const std::vector<std::vector<int>> &solution, bool PRINT1 = false) {
        PRINT = PRINT1;
        Sudoku = grid;
        Author_Solution = solution;
        for (int row = 0; row < Size * Size; ++row) {
            for (int column = 0; column < Size * Size; ++column) {
                if (Sudoku[row][column] == 0) {
                    continue;
                }
                FillCell(row, column, Sudoku[row][column]);
            }
        }
        Finder();
    }

    void print() {
        for (int i = 0; i < Size * Size; ++i) {
            for (int j = 0; j < Size * Size; ++j) {
                std::cerr << Sudoku[j][i] << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << '\n';
    }

    bool PRINT = false;

private:

    int iterAmount = 0;
    int depth = 0;

    void Finder(int curPos = 0) {
        int row = curPos / 9;
        int column = curPos % 9;
        if (curPos == 81) {
            IsAnsFound = true;
            if (Sudoku != Author_Solution) {
                IsUniqueSolution = false;
            }
            if (PRINT) {
                print();
            }
            return;
        }
        if (!PRINT && !IsUniqueSolution) {
            return;
        }
        if (Sudoku[row][column]) {
            return Finder(curPos + 1);
        }
        int box = row - row % 3 + column / 3;
        for (int number = 1; number <= 9; ++number) {
            if ((BoxesBitmasks[box] >> number & 1)
                || (RowsBitmasks[row] >> number & 1)
                || (ColumnsBitmasks[column] >> number & 1)) {
                continue;
            }
            FillCell(row, column, number);
            ++depth;
            Finder(curPos + 1);
            --depth;
            ClearCell(row, column);
        }
    }

    void FillCell(int row, int column, int value) {
        Sudoku[row][column] = value;
        const int MASK = (1 << value);
        RowsBitmasks[row] |= MASK;
        ColumnsBitmasks[column] |= MASK;
        BoxesBitmasks[row - row % 3 + column / 3] |= MASK;
    }

    void ClearCell(int row, int column) {
        int value = Sudoku[row][column];
        const int MASK = (1 << value);
        RowsBitmasks[row] -= MASK;
        ColumnsBitmasks[column] -= MASK;
        BoxesBitmasks[row - row % 3 + column / 3] -= MASK;
        Sudoku[row][column] = 0;
    }

};