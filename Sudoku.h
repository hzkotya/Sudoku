#pragma once
#include <iostream>
#include <vector>
#include "Random.h"
#include "Validator.h"

constexpr int Size = 3;
class Sudoku {
public:
    int FilledCount = 0;
    std::vector<std::vector<int>> Current;
    std::vector<int> RowsBitmasks;
    std::vector<int> ColumnsBitmasks;
    std::vector<int> BoxesBitmasks;
    std::vector<int> regimes;

    void printans() {
        for (int i = 0; i < Size * Size; ++i) {
            for (int j = 0; j < Size * Size; ++j) {
                std::cerr << Answer[j][i] << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << '\n';
        std::cerr << '\n';
    }

    void print() {
        for (int i = 0; i < Size * Size; ++i) {
            for (int j = 0; j < Size * Size; ++j) {
                std::cerr << Current[j][i] << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << '\n';
    }

    explicit Sudoku(int regime) {
        regimes = {25, 38, 55};
        Answer.assign(Size * Size, std::vector<int>(Size * Size));
        for (int index_first = 0; index_first < Size * Size; ++index_first) {
            for (int index_second = 0; index_second < Size * Size; ++index_second) {
                Answer[index_first][index_second] = (
                        (index_first * Size + index_first / Size + index_second) % (Size * Size) + 1);
            }
        }
        MixGrid();
        Current = Answer;
        std::vector<std::pair<int, int>> positions;
        for (int row = 0; row < Size * Size; ++row) {
            for (int column = 0; column < Size * Size; ++column) {
                positions.emplace_back(row, column);
            }
        }
        std::shuffle(positions.begin(), positions.end(), rnd);
        int cnt = 0;
        for (auto [row, column] : positions) {
            if (cnt > regimes[regime]) {
                break;
            }
            auto NewGrid = Current;
            NewGrid[row][column] = 0;
            if (!SudokuValidator(NewGrid, Answer).IsUniqueSolution) {
                continue;
            }
            cnt++;
            Current = NewGrid;
        }
        auto x = SudokuValidator(Current, Answer);
        x.print();
        std::cerr << x.IsAnsFound << '\n';
        std::cerr << cnt << '\n';
        for (int row = 0; row < Size * Size; ++row) {
            for (int column = 0; column < Size * Size; ++column) {
                if (Current[row][column] != 0) {
                    FilledCount++;
                }
            }
        }
    }

    bool Fill(int row, int column, int value) {
        if (Check(row, column, value)) {
            Current[row][column] = value;
        } else {
            std::cerr << "JA PIERDOLĘ\n";
            return false;
        }
//        print();
        return true;
        if (FilledCount == Size * Size * Size * Size) {
            std::cerr << "YOU WON!!\n";
            exit(0);
        }
    }


private:
    std::vector<std::vector<int>> Answer;

    [[nodiscard]] bool Check(int row, int column, int value) const {
        if (Answer[row][column] != value) {
            return false;
        }
        return true;

    }

    void SwapRows() {
        int box = GetRandomNumber(Size);
        int first_row = GetRandomNumber(Size);
        int second_row = GetRandomNumber(Size);
        std::swap(Answer[first_row + Size * box], Answer[second_row + Size * box]);
    }

    void SwapColumns() {
        int box = GetRandomNumber(Size);
        int first_column = GetRandomNumber(Size);
        int second_column = GetRandomNumber(Size);
        for (int row = 0; row < Size * Size; ++row) {
            std::swap(Answer[row][first_column + Size * box], Answer[row][second_column + Size * box]);
        }
    }

    void SwapVerticalBoxes() {
        int first_box = GetRandomNumber(Size);
        int second_box = GetRandomNumber(Size);
        for (int row = 0; row < Size * Size; ++row) {
            for (int column = 0; column < Size; ++column) {
                std::swap(Answer[row][column + Size * first_box], Answer[row][column + Size * second_box]);
            }
        }
    }

    void SwapHorizontalBoxes() {
        int first_box = GetRandomNumber(Size);
        int second_box = GetRandomNumber(Size);
        for (int row = 0; row < Size; ++row) {
            for (int column = 0; column < Size * Size; ++column) {
                std::swap(Answer[row + Size * first_box][column], Answer[row + Size * second_box][column]);
            }
        }
    }

    void MixGrid() {
        for (int iteration = 0; iteration < 100; ++iteration) {
            SwapRows();
            SwapColumns();
            SwapVerticalBoxes();
            SwapHorizontalBoxes();
        }
    }


};


Sudoku sudoku(2);