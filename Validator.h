#include <vector>
#include <cmath>
#include <algorithm>
#include <set>


class SudokuValidator {

public:
    const int Size = 3;
    bool IsUniqueSolution = true;

    std::multiset<std::pair<int, int>, std::greater<>> CounterSet;
    std::vector<int> CounterVector;
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
        CounterVector.resize(Size * Size);
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

private:

    void Finder() {
        if (CounterSet.empty() && Sudoku != Author_Solution) {
            IsUniqueSolution = false;
        }
        if (CounterSet.empty() || !IsUniqueSolution) {
            return;
        }
        int number = CounterSet.begin()->second;
        for (int box = 0; box < Size * Size && IsUniqueSolution; ++box) {
            if (BoxesBitmasks[box] & (1 << number)) {
                continue;
            }
            for (int row = Size * (box / Size); row < Size * (box / Size + 1); ++row) {
                for (int column = Size * (box % Size); column < Size * (box % Size + 1); ++column) {
                    if (!(RowsBitmasks[row] & (1 << number)) && !(ColumnsBitmasks[column] & (1 << number))) {
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
        RowsBitmasks[row] |= (1 << Sudoku[row][column]);
        ColumnsBitmasks[column] |= (1 << Sudoku[row][column]);
        BoxesBitmasks[row / 3 * 3 + column / 3] |= (1 << Sudoku[row][column]);
        CounterSet.erase({CounterVector[Sudoku[row][column]], Sudoku[row][column]});
        if (++CounterVector[Sudoku[row][column]] < Size * Size) {
            CounterSet.emplace(CounterVector[Sudoku[row][column]], Sudoku[row][column]);
        }
    }

    void ClearCell(int row, int column) {
        RowsBitmasks[row] -= (1 << Sudoku[row][column]);
        ColumnsBitmasks[column] -= (1 << Sudoku[row][column]);
        BoxesBitmasks[row / 3 * 3 + column / 3] -= (1 << Sudoku[row][column]);
        CounterSet.erase({CounterVector[Sudoku[row][column]], Sudoku[row][column]});
        if (--CounterVector[Sudoku[row][column]] < Size * Size) {
            CounterSet.emplace(CounterVector[Sudoku[row][column]], Sudoku[row][column]);
        }
        Sudoku[row][column] = 0;
    }

};