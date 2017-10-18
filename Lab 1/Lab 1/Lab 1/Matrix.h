#pragma once
#include <iostream>
#include <array>
#include <sstream>
#include "Fraction.h"

template<typename T, unsigned SZ>
class Matrix
{
    std::array<std::array<T, SZ>, SZ> matrix;
    
    void fill(const T & e);

    void swapColumn(unsigned first, unsigned second) {
        if (first >= SZ || second >= SZ)
            return;

        for (unsigned i = 0; i < SZ; i++) {
            std::swap(this->matrix[i][first], this->matrix[i][second]);
        }
    }

    void swapLines(unsigned first, unsigned second) {
        if (first >= SZ || second >= SZ)
            return;

        for (unsigned i = 0; i < SZ; i++) {
            std::swap(this->matrix[first][i], this->matrix[second][i]);
        }
    }

public:
    Matrix() { fill(T()); };
    Matrix(const T & e) { fill(e); };

    Matrix(int i) : Matrix(Fraction<int>(i)) { }


    Matrix<T, SZ> & operator*=(const T & elem);

    Matrix<T, SZ> & operator+=(const Matrix<T, SZ> & matrix);

    Matrix<T, SZ> & operator*=(const Matrix<T, SZ> & matrix);

    Matrix<T, SZ> & operator/=(const Matrix<T, SZ> & matrix);

    Matrix<T, SZ> operator-() {
        Matrix<T, SZ> tmp;

        for (unsigned i = 0; i < SZ; i++) {
            for (unsigned k = 0; k < SZ; k++) {
                tmp.matrix[i][k] = -(this->matrix[i][k]);
            }
        }

        return tmp;
    }

    T determinant() const {
        T empty{};
        Matrix<T, SZ> tmp = *this;

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

                T coef = tmp.matrix[inner_line][line] / tmp.matrix[line][line];

                for (unsigned inner_col = line; inner_col < SZ; inner_col++) {
                    tmp.matrix[inner_line][inner_col] -= (coef * tmp.matrix[line][inner_col]);
                }
            }
        }


        T result = tmp.matrix[0][0];

        for (unsigned i = 1; i < SZ; i++) {
            result *= tmp.matrix[i][i];
        }

        return result;
    }

    Matrix<T, SZ> inverse() const {
        T determ = this->determinant();
        T zero{};
        if (determ == zero) {
            throw std::runtime_error("determinant = 0");
        }

        Matrix<T, SZ> tmp{ *this };

        Matrix<T, SZ> inversed{ zero };
        for (unsigned i = 0; i < SZ; i++) {
            inversed.matrix[i][i] = T(1);
        }

        for (unsigned line = 0; line < SZ; line++) {
            if (tmp.matrix[line][line] == zero) {
                for (unsigned inner_line = line + 1; inner_line < SZ; inner_line++) {
                    if (tmp.matrix[inner_line][line] != zero) {
                        tmp.swapLines(line, inner_line);
                        inversed.swapLines(line, inner_line);
                    }
                }
            }

            if (tmp.matrix[line][line] == zero) {
                throw std::runtime_error("determinant = 0");
            }

            for (unsigned inner_line = line + 1; inner_line < SZ; inner_line++) {
                T coef = tmp.matrix[inner_line][line] / tmp.matrix[line][line];

                for (unsigned inner_col = 0; inner_col < SZ; inner_col++) {
                    tmp.matrix[inner_line][inner_col] -= (coef * tmp.matrix[line][inner_col]);
                    inversed.matrix[inner_line][inner_col] -= (coef * inversed.matrix[line][inner_col]);
                }
            }
        }

        for (unsigned i = 0; i < (SZ / 2); i++) {
            tmp.swapLines(i, SZ - 1 - i);
            inversed.swapLines(i, SZ - 1 - i);
        }

        for (unsigned i = 0; i < (SZ / 2); i++) {
            tmp.swapColumn(i, SZ - 1 - i);
            inversed.swapColumn(i, SZ - 1 - i);
        }

        for (unsigned line = 0; line < SZ; line++) {
            if (tmp.matrix[line][line] == zero) {
                for (unsigned inner_line = line + 1; inner_line < SZ; inner_line++) {
                    if (tmp.matrix[inner_line][line] != zero) {
                        tmp.swapLines(line, inner_line);
                        inversed.swapLines(line, inner_line);
                    }
                }
            }

            if (tmp.matrix[line][line] == zero) {
                throw std::runtime_error("determinant = 0");
            }


            for (unsigned inner_line = line + 1; inner_line < SZ; inner_line++) {
                T coef = tmp.matrix[inner_line][line] / tmp.matrix[line][line];

                for (unsigned inner_col = 0; inner_col < SZ; inner_col++) {
                    tmp.matrix[inner_line][inner_col] -= (coef * tmp.matrix[line][inner_col]);
                    inversed.matrix[inner_line][inner_col] -= (coef * inversed.matrix[line][inner_col]);
                }
            }
        }

        for (unsigned i = 0; i < (SZ / 2); i++) {
            tmp.swapLines(i, SZ - 1 - i);
            inversed.swapLines(i, SZ - 1 - i);
        }

        for (unsigned i = 0; i < (SZ / 2); i++) {
            tmp.swapColumn(i, SZ - 1 - i);
            inversed.swapColumn(i, SZ - 1 - i);
        }

        for (unsigned i = 0; i < SZ; i++) {
            T one(1);
            one /= tmp.matrix[i][i];
            for (unsigned k = 0; k < SZ; k++) {
                inversed.matrix[i][k] *= one;
            }
        }

        return inversed;
    }
    
    bool operator==( Matrix<T, SZ> m) {
        for (unsigned line = 0; line < SZ; line++) {
            for (unsigned col = 0; col < SZ; col++) {
                if (this->matrix[line][col] != m.matrix[line][col]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator>(const Matrix<T, SZ> m) {
        return !(*this == m);
    }

    bool operator!=(const Matrix<T, SZ> m) {
        return !(*this == m);
    }
    
    friend std::ostream & operator<<(std::ostream & os, const Matrix<T, SZ> & m) {
        for (auto row : m.matrix) {
            os << '|';            
            for (auto cell : row) {
                os.width(8);
                os << cell << ", ";
            }
            os << "\b\b|\n";
        }
        return os;
    }

    template<typename T, typename Stream>
    friend Stream & operator>>(Stream & is, Matrix<T, SZ> & m) {
        int i = 1;
        for (auto & row : m.matrix) {
            string input;
            std::getline(is, input);
            istringstream iss(input);
            for (auto & cell : row) {
                iss >> cell;
            }
        }
        return is;
    }

};

template<typename T, unsigned SZ>
inline void Matrix<T, SZ>::fill(const T & e)
{
    for (auto & row : matrix) {
        for (auto & cell : row) {
            cell = e;
        }
    }
}

template<typename T, unsigned SZ>
inline Matrix<T, SZ> & Matrix<T, SZ>::operator*=(const T & elem)
{
    for (auto & row : matrix) {
        for (auto & cell : row) {
            cell *= elem;
        }
    }

    return *this;
}

template<typename T, unsigned SZ>
inline Matrix<T, SZ>& Matrix<T, SZ>::operator*=(const Matrix<T, SZ>& m)
{
    Matrix<T, SZ> tmp;

    for (int i = 0; i < SZ; i++)
        for (int k = 0; k < SZ; k++)
            for (int j = 0; j < SZ; j++) {
                tmp.matrix[i][k] += this->matrix[i][j] * m.matrix[j][k];
            }

    return *this = tmp;
}


template<typename T, unsigned SZ>
Matrix<T, SZ> operator*(const Matrix<T, SZ>& m1, const Matrix<T, SZ> &m2)
{
    auto tmp = m1;

    return tmp *= m2;
}

template<typename T, unsigned SZ>
Matrix<T, SZ> operator*(const Matrix<T, SZ>& m1, const T & elem)
{
    auto tmp = m1;

    return tmp *= elem;
}


template<typename T, unsigned SZ>
inline Matrix<T, SZ> & Matrix<T, SZ>::operator+=(const Matrix<T, SZ> & m)
{
    for (int i = 0; i < SZ; i++) {
        for (int j = 0; j < SZ; j++) {
            matrix[i][j] += m.matrix[i][j];
        }
    }

    return *this;
}

template<typename T, unsigned SZ>
Matrix<T, SZ> operator+(const Matrix<T, SZ> & m1, const Matrix<T, SZ> & m2)
{
    auto tmp = m1;

    return tmp += m2;
}


template<typename T, unsigned SZ>
inline Matrix<T, SZ>& Matrix<T, SZ>::operator/=(const Matrix<T, SZ>& m)
{
    return *this *= m.inverse();
}

template<typename T, unsigned SZ>
Matrix<T, SZ> operator/(const Matrix<T, SZ>& m1, const Matrix<T, SZ>& m2)
{
    auto tmp = m1;
 
    return tmp /= m2;
}

template <typename T>
struct NumberConstraint<Fraction<T>>
{
    static const constexpr Fraction<T> One = Fraction<T>(NumberConstraint<T>::One);
    static const constexpr Fraction<T> Zero = Fraction<T>(NumberConstraint<T>::Zero);
};

template <typename T, size_t SZ>
struct NumberConstraint<Matrix<T, SZ>>
{
    static const constexpr Matrix<T, SZ> One = Matrix<T, SZ>(NumberConstraint<T>::One);
    static const constexpr Matrix<T, SZ> Zero = Matrix<T, SZ>(NumberConstraint<T>::Zero);
};