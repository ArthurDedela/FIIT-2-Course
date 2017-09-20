#pragma once
#include <iostream>

template<typename TYPE>
class Fraction
{
    TYPE numerator, denominator;

    void toCommonDenominator(Fraction<TYPE> & f1, Fraction<TYPE> & f2);

public:
    Fraction() : numerator(0), denominator(1) {};

    Fraction(TYPE Numerator, TYPE Denominator) : numerator(Numerator), denominator(Denominator) {};


    Fraction<TYPE> & operator+=(const Fraction<TYPE> & fraction);
    Fraction<TYPE> operator+(const Fraction<TYPE> & fraction);

    Fraction<TYPE> & operator-=(const Fraction<TYPE> & fraction);
    Fraction<TYPE> operator-(const Fraction<TYPE> & fraction);

    Fraction<TYPE> & operator*=(const Fraction<TYPE> & fraction);
    Fraction<TYPE> operator*(const Fraction<TYPE> & fraction);

    Fraction<TYPE> & operator/=(const Fraction<TYPE> & fraction);
    Fraction<TYPE> operator/(const Fraction<TYPE> & fraction);

    bool operator==(const Fraction<TYPE> & fraction);
    bool operator!=(const Fraction<TYPE> & fraction);


    friend std::ostream & operator<<(std::ostream & os, const Fraction<TYPE> & f) {
        os << f.numerator << " / " << f.denominator;
        return os;
    }

    friend std::istream & operator>>(std::istream & is, Fraction<TYPE> & f) {
        char c;
        is >> f.numerator >> c >> f.denominator;

        return is;
    }

    //~Fraction();
};

template<typename TYPE>
inline void Fraction<TYPE>::toCommonDenominator(Fraction<TYPE> & f1, Fraction<TYPE> & f2)
{
    f1.numerator *= f2.denominator;
    f2.numerator *= f1.denominator;

    f2.denominator = (f1.denominator *= f2.denominator);
}

template<typename TYPE>
inline Fraction<TYPE> & Fraction<TYPE>::operator+=(const Fraction<TYPE> & f)
{
    if (denominator != f.denominator) {
        auto tmp = f;
        toCommonDenominator(*this, tmp);
        numerator += tmp.numerator;
    }
    else {
        numerator += f.numerator;
    }

    return *this;
}

template<typename TYPE>
inline Fraction<TYPE> Fraction<TYPE>::operator+(const Fraction<TYPE>& f)
{
    auto tmp = *this;
    tmp += f;

    return tmp;
}

template<typename TYPE>
inline Fraction<TYPE>& Fraction<TYPE>::operator-=(const Fraction<TYPE>& f)
{
    if (denominator != f.denominator) {
        auto tmp = f;
        toCommonDenominator(*this, tmp);
        numerator -= tmp.numerator;
    }
    else {
        numerator -= f.numerator;
    }

    return *this;
}

template<typename TYPE>
inline Fraction<TYPE> Fraction<TYPE>::operator-(const Fraction<TYPE>& f)
{
    auto tmp = *this;
    tmp -= f;

    return tmp;
}

template<typename TYPE>
inline Fraction<TYPE> & Fraction<TYPE>::operator*=(const Fraction<TYPE>& f)
{
    numerator *= f.numerator;
    denominator *= f.denominator;

    return *this;
}

template<typename TYPE>
inline Fraction<TYPE> Fraction<TYPE>::operator*(const Fraction<TYPE>& f)
{
    auto tmp = *this;
    tmp *= f;

    return tmp;
}

template<typename TYPE>
inline Fraction<TYPE>& Fraction<TYPE>::operator/=(const Fraction<TYPE>& f)
{
    *this *= Fraction<TYPE>(f.denominator, f.numerator);

    return *this;
}

template<typename TYPE>
inline Fraction<TYPE> Fraction<TYPE>::operator/(const Fraction<TYPE>& f)
{
    auto tmp = *this;
    tmp /= f;

    return tmp;
}

template<typename TYPE>
inline bool Fraction<TYPE>::operator==(const Fraction<TYPE>& f)
{
    auto f_1 = *this, f_2 = f;

    if (denominator != f.denominator) {
        toCommonDenominator(f_1, f_2);
    }

    return f_1.numerator == f_2.numerator;
}

template<typename TYPE>
inline bool Fraction<TYPE>::operator!=(const Fraction<TYPE>& f)
{
    return !(*this == f);
}

