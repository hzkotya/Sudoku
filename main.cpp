#include <iostream>
#include <vector>
#include "Random.h"
#include "Validator.h"

class Sudoku {
public:
    const int Size = 3;
    int FilledCount = 0;
    std::vector<std::vector<int>> Current;
    std::vector<int> RowsBitmasks;
    std::vector<int> ColumnsBitmasks;
    std::vector<int> BoxesBitmasks;

    void printans() {
        for (int i = 0; i < Size * Size; ++i) {
            for (int j = 0; j < Size * Size; ++j) {
                std::cerr << _Answer[i][j] << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << '\n';
        std::cerr << '\n';
    }

    void print() {
        for (int i = 0; i < Size * Size; ++i) {
            for (int j = 0; j < Size * Size; ++j) {
                std::cerr << Current[i][j] << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << '\n';
    }

    explicit Sudoku() {
        _Answer.assign(Size * Size, std::vector<int>(Size * Size));
        for (int index_first = 0; index_first < Size * Size; ++index_first) {
            for (int index_second = 0; index_second < Size * Size; ++index_second) {
                _Answer[index_first][index_second] = (
                        (index_first * Size + index_first / Size + index_second) % (Size * Size) + 1);
            }
        }
        _MixGrid();
        Current = _Answer;
        std::vector<std::pair<int, int>> positions;
        for (int row = 0; row < Size * Size; ++row) {
            for (int column = 0; column < Size * Size; ++column) {
                positions.emplace_back(row, column);
            }
        }
        std::shuffle(positions.begin(), positions.end(), rnd);
        for (auto [row, column] : positions) {
            auto NewGrid = Current;
            NewGrid[row][column] = 0;
            if (!SudokuValidator(NewGrid, _Answer).IsUniqueSolution) {
                continue;
            }
            Current = NewGrid;
        }
        for (int row = 0; row < Size * Size; ++row) {
            for (int column = 0; column < Size * Size; ++column) {
                if (Current[row][column] != 0) {
                    FilledCount++;
                }
            }
        }
    }

    void Fill(int row, int column, int value) {
        if (_Check(row, column, value)) {
            Current[row][column] = value;
            FilledCount++;
        } else {
            std::cerr << "JA PIERDOLĘ\n";
        }
        print();
        if (FilledCount == Size * Size * Size * Size) {
            std::cerr << "YOU WON!!\n";
            exit(0);
        }
    }

    void Fill() {
        int row;
        int column;
        int value;
        std::cin >> row >> column >> value;
        if (_Check(row, column, value)) {
            Current[row][column] = value;
        } else {
            std::cerr << "JA PIERDOLĘ\n";
        }
        print();
        if (FilledCount == Size * Size * Size * Size) {
            std::cerr << "YOU WON!!\n";
            exit(0);
        }
    }


private:
    std::vector<std::vector<int>> _Answer;

    bool _Check(int row, int column, int value) const {
        if (_Answer[row][column] != value) {
            return false;
        }
        return true;

    }

    void _SwapRows() {
        int box = GetRandomNumber(Size);
        int first_row = GetRandomNumber(Size);
        int second_row = GetRandomNumber(Size);
        std::swap(_Answer[first_row + Size * box], _Answer[second_row + Size * box]);
    }

    void SwapColumns() {
        int box = GetRandomNumber(Size);
        int first_column = GetRandomNumber(Size);
        int second_column = GetRandomNumber(Size);
        for (int row = 0; row < Size * Size; ++row) {
            std::swap(_Answer[row][first_column + Size * box], _Answer[row][second_column + Size * box]);
        }
    }

    void _SwapVerticalBoxes() {
        int first_box = GetRandomNumber(Size);
        int second_box = GetRandomNumber(Size);
        for (int row = 0; row < Size * Size; ++row) {
            for (int column = 0; column < Size; ++column) {
                std::swap(_Answer[row][column + Size * first_box], _Answer[row][column + Size * second_box]);
            }
        }
    }

    void _SwapHorizontalBoxes() {
        int first_box = GetRandomNumber(Size);
        int second_box = GetRandomNumber(Size);
        for (int row = 0; row < Size; ++row) {
            for (int column = 0; column < Size * Size; ++column) {
                std::swap(_Answer[row + Size * first_box][column], _Answer[row + Size * second_box][column]);
            }
        }
    }

    void _MixGrid() {
        for (int iteration = 0; iteration < 100; ++iteration) {
            _SwapRows();
            SwapColumns();
            _SwapVerticalBoxes();
            _SwapHorizontalBoxes();
        }
    }


};

int main() {
    auto s = Sudoku();
    s.printans();
    s.print();
    while (true) {
       s.Fill();
    }
    return 0;
}