#include <iostream>
#include <vector>
#include <random>
#include <chrono>
class Sudoku {

public:

    std::vector<std::vector<int>> Current;

    void print() {
        for (int i = 0; i < _Size * _Size; ++i) {
            for (int j = 0; j < _Size * _Size; ++j) {
                std::cerr << _Answer[i][j] << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << '\n';
    }

    explicit Sudoku(int grid_size) {
        _Size = grid_size;
        _Answer.assign(_Size * _Size, std::vector<int>(_Size * _Size));
        for (int index_first = 0; index_first < _Size * _Size; ++index_first) {
            for (int index_second = 0; index_second < _Size * _Size; ++index_second) {
                _Answer[index_first][index_second] = (
                        (index_first * _Size + index_first / _Size + index_second) % (_Size * _Size) + 1);
            }
        }
        print();
        _MixGrid();

    }


private:

    int _Size;
    std::vector<std::vector<int>> _Answer;
    const int _Seed{static_cast<int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::mt19937 _Random{static_cast<unsigned int>(_Seed)};

    int _GetRandomNumber(int left_bound, int right_bound) {
        return left_bound + _Random() % (right_bound - left_bound);
    }

    bool _Check(int row, int column, int value) const {
        if (_Answer[row][column] != value) {
            return false;
        }
        return true;
    }

    void _SwapRows() {
        int area = _GetRandomNumber(0, _Size);
        int first_row = _GetRandomNumber(0, _Size);
        int second_row = _GetRandomNumber(0, _Size);
        std::swap(_Answer[first_row + _Size * area], _Answer[second_row + _Size * area]);
    }

    void SwapColumns() {
        int area = _GetRandomNumber(0, _Size);
        int first_column = _GetRandomNumber(0, _Size);
        int second_column = _GetRandomNumber(0, _Size);
        for (int index = 0; index < _Size; ++index) {
            std::swap(_Answer[index][first_column + _Size * area], _Answer[index][second_column + _Size * area]);
        }
    }

    void _SwapVerticalAreas() {
        int column = _GetRandomNumber(0, _Size);
        int first_area = _GetRandomNumber(0, _Size);
        int second_area = _GetRandomNumber(0, _Size);
        for (int index_first = 0; index_first < _Size; ++index_first) {
            for (int index_second = 0; index_second < _Size; ++index_second) {
                std::swap(_Answer[index_second + _Size * first_area][index_first + _Size * column],
                          _Answer[index_second + _Size * second_area][index_first + _Size * column]);
            }
        }
    }


    void _SwapHorizontalAreas() {
        int row = _GetRandomNumber(0, _Size);
        int first_area = _GetRandomNumber(0, _Size);
        int second_area = _GetRandomNumber(0, _Size);
        for (int index_first = 0; index_first < _Size; ++index_first) {
            for (int index_second = 0; index_second < _Size; ++index_second) {
                std::swap(_Answer[index_first + _Size * row][index_second + _Size * first_area],
                          _Answer[index_second + _Size * row][index_second + _Size * second_area]);
            }
        }
    }

    void _MixGrid() {
        for (int iteration = 0; iteration < 100; ++iteration) {
            _SwapRows();
            SwapColumns();
            _SwapVerticalAreas();
            _SwapHorizontalAreas();
        }
    }

};

int main() {
    auto s = Sudoku(3);
    s.print();
    return 0;
}