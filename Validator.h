#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>


class SudokuValidator {

public:
    static const int Size = 3;
    bool IsUniqueSolution = true;
    bool IsAnsFound = false;

    std::vector<int> Counter;
    std::vector<int> RowsBitmasks;
    std::vector<int> ColumnsBitmasks;
    std::vector<int> BoxesBitmasks;
    std::vector<std::vector<int>> Sudoku;
    std::vector<std::vector<int>> Author_Solution;

    explicit SudokuValidator(const std::vector<std::vector<int>> &grid, const std::vector<std::vector<int>> &solution) {
        Sudoku = grid;
        Author_Solution = solution;
        RowsBitmasks.resize(Size * Size);
        ColumnsBitmasks.resize(Size * Size);
        BoxesBitmasks.resize(Size * Size);
        Counter.resize(Size * Size);
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
        for (auto i: Sudoku) {
            for (auto j: i) {
                std::cerr << j << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << '\n';
    }

private:

    void Finder() {
        int number = 0;
        for (int value = 1; value <= Size * Size; ++value) {
            if (Counter[value] < Size * Size && (!number || Counter[value] > Counter[number])) {
                number = value;
            }
        }

        if (!number && Sudoku == Author_Solution) {
            IsAnsFound = true;
        }
        if (!number && Sudoku != Author_Solution) {
            IsAnsFound = true;
            IsUniqueSolution = false;
        }
        if (!number || !IsUniqueSolution) {
            return;
        }
        for (int box = 0; box < Size * Size && IsUniqueSolution; ++box) {
            if (BoxesBitmasks[box] & (1 << number)) {
                continue;
            }
            for (int row = Size * (box / Size); row < Size * (box / Size + 1); ++row) {
                for (int column = Size * (box % Size); column < Size * (box % Size + 1); ++column) {
                    if (!Sudoku[row][column] && !(RowsBitmasks[row] & (1 << number)) &&
                        !(ColumnsBitmasks[column] & (1 << number))) {
                        FillCell(row, column, number);
                        Finder();
                        ClearCell(row, column);
                    }
                }
            }
        }
    }

    void FillCell(int row, int column, int value) {
        Sudoku[row][column] = value;
        assert(!(RowsBitmasks[row] & (1 << Sudoku[row][column])));
        assert(!(ColumnsBitmasks[column] & (1 << Sudoku[row][column])));
        assert(!(BoxesBitmasks[row / 3 * 3 + column / 3] & (1 << Sudoku[row][column])));
        RowsBitmasks[row] |= (1 << Sudoku[row][column]);
        ColumnsBitmasks[column] |= (1 << Sudoku[row][column]);
        BoxesBitmasks[row / 3 * 3 + column / 3] |= (1 << Sudoku[row][column]);
        ++Counter[Sudoku[row][column]];
    }

    void ClearCell(int row, int column) {
        assert(RowsBitmasks[row] & (1 << Sudoku[row][column]));
        assert(ColumnsBitmasks[column] & (1 << Sudoku[row][column]));
        assert(BoxesBitmasks[row / 3 * 3 + column / 3] & (1 << Sudoku[row][column]));
        RowsBitmasks[row] -= (1 << Sudoku[row][column]);
        ColumnsBitmasks[column] -= (1 << Sudoku[row][column]);
        BoxesBitmasks[row / 3 * 3 + column / 3] -= (1 << Sudoku[row][column]);
        --Counter[Sudoku[row][column]];
        Sudoku[row][column] = 0;
    }

};
