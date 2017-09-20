#pragma once
#include <iostream>
#include <array>
#include <sstream>

template<typename TYPE, unsigned SZ>
class Matrix
{
    std::array<std::array<TYPE, SZ>, SZ> matrix;
    
    void fill(const TYPE & e);

public:
    Matrix() { fill(TYPE()); };
    Matrix(const TYPE & e) { fill(e); };

    Matrix<TYPE, SZ> & operator*=(const TYPE & elem);
    Matrix<TYPE, SZ> operator*(const TYPE & elem);

    Matrix<TYPE, SZ> & operator+=(const Matrix<TYPE, SZ> & matrix);
    Matrix<TYPE, SZ> operator+(const Matrix<TYPE, SZ> & matrix);

    Matrix<TYPE, SZ> & operator*=(const Matrix<TYPE, SZ> & matrix);
    Matrix<TYPE, SZ> operator*(const Matrix<TYPE, SZ> & matrix);

    TYPE determinant();

    void swapLines(unsigned first, unsigned second) {
        if (first >= SZ || second >= SZ)
            return;

        for (unsigned i = 0; i < SZ; i++) {
            std::swap(this->matrix[first][i], this->matrix[second][i]);
        }
    }


    friend std::ostream & operator<<(std::ostream & os, const Matrix<TYPE, SZ> & m) {
        for (auto row : m.matrix) {
            os << '|';
            for (auto cell : row) {
                os << cell << ", ";
            }
            os << "\b\b|\n";
        }
        return os;
    }

    friend std::istream & operator>>(std::istream & is, Matrix<TYPE, SZ> & m) {
        int i = 1;
        for (auto & row : m.matrix) {
            string input;
            cout << "Enter " << i++ << " row: ";
            std::getline(is, input);
            istringstream oss(input);
            for (auto & cell : row) {
                oss >> cell;
            }
        }
        return is;
    }


};

template<typename TYPE, unsigned SZ>
inline void Matrix<TYPE, SZ>::fill(const TYPE & e)
{
    for (auto & row : matrix) {
        for (auto & cell : row) {
            cell = e;
        }
    }
}

template<typename TYPE, unsigned SZ>
inline Matrix<TYPE, SZ> & Matrix<TYPE, SZ>::operator*=(const TYPE & elem)
{
    for (auto & row : matrix) {
        for (auto & cell : row) {
            cell *= elem;
        }
    }

    return *this;
}

template<typename TYPE, unsigned SZ>
inline Matrix<TYPE, SZ> Matrix<TYPE, SZ>::operator*(const TYPE & elem)
{
    auto tmp = *this;

    return tmp *= elem;
}


template<typename TYPE, unsigned SZ>
inline Matrix<TYPE, SZ> & Matrix<TYPE, SZ>::operator+=(const Matrix<TYPE, SZ> & m)
{
    for (int i = 0; i < SZ; i++) {
        for (int j = 0; j < SZ; j++) {
            matrix[i][j] += m.matrix[i][j];
        }
    }

    return *this;
}

template<typename TYPE, unsigned SZ>
inline Matrix<TYPE, SZ> Matrix<TYPE, SZ>::operator+(const Matrix<TYPE, SZ> & m)
{
    auto tmp = *this;

    return tmp += m;
}

template<typename TYPE, unsigned SZ>
inline Matrix<TYPE, SZ>& Matrix<TYPE, SZ>::operator*=(const Matrix<TYPE, SZ>& m)
{
    Matrix<TYPE, SZ> tmp;

    for (int i = 0; i < SZ; i++)
        for (int k = 0; k < SZ; k++)
            for (int j = 0; j < SZ; j++) {
                tmp.matrix[i][k] += this->matrix[i][j] * m.matrix[j][k];
            }
    
    return *this = tmp;
}

template<typename TYPE, unsigned SZ>
inline Matrix<TYPE, SZ> Matrix<TYPE, SZ>::operator*(const Matrix<TYPE, SZ>& m)
{
    auto tmp = *this;
    
    return tmp *= m;
}

template<typename TYPE, unsigned SZ>
inline TYPE Matrix<TYPE, SZ>::determinant()
{
    TYPE empty{};
    Matrix<TYPE, SZ> tmp = *this;

    for (unsigned line = 0; line < SZ; line++) {

        if (tmp.matrix[line][line] == empty) {
            for (unsigned inner_line = line + 1; inner_line < SZ; inner_line++) {
                if (tmp.matrix[inner_line][line] != empty) {
                    tmp.swapLines(line, inner_line);
                }
            }
        }

        if (tmp.matrix[line][line] == empty) {
            return empty;
        }


        for (unsigned inner_line = line + 1; inner_line < SZ; inner_line++) {

            TYPE coef = tmp.matrix[inner_line][line] / tmp.matrix[line][line];

            for (unsigned inner_col = line; inner_col < SZ; inner_col++) {
                tmp.matrix[inner_line][inner_col] -= (coef * tmp.matrix[line][inner_col]);
            }
        }
    }


    TYPE result = tmp.matrix[0][0];

    for (unsigned i = 1; i < SZ; i++) {
        result *= tmp.matrix[i][i];
    }

    return result;
}

