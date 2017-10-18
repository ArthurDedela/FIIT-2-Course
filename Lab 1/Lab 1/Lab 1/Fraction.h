#ifndef FRACTION_H
#define FRACTION_H

#include <string>
#include <sstream>
#include <stdexcept>


template <typename T>
struct NumberConstraint
{
};

template <>
struct NumberConstraint <int>
{
    static constexpr int One = 1;
    static constexpr int Zero = 0;
};

template <>
struct NumberConstraint <long long>
{
    static constexpr long long One = 1;
    static constexpr long long Zero = 0;
};

template <typename T>
class Fraction
{
public:
    using CRef = const Fraction &;

    Fraction() : _numerator(NumberConstraint<T>::Zero), _denumerator(NumberConstraint<T>::One) {}

    explicit Fraction(T number) : Fraction(number, NumberConstraint<T>::One) {}

    Fraction(T numerator, T denumerator) :
        _numerator(numerator)
    {
        if (denumerator == NumberConstraint<T>::Zero) {
            throw std::runtime_error("Denumerator equals to 0");
        }

        _denumerator = denumerator;
    }

    Fraction & operator += (CRef rhs) {
        T multiplier = Lcm(_denumerator, rhs._denumerator);

        _numerator = this->Multiply(multiplier) + rhs.Multiply(multiplier);
        _denumerator = multiplier;

        return this->Simplify();
    }

    Fraction & operator-= (CRef rhs) {
        return (*this) += -rhs;
    }

    Fraction & operator *= (CRef rhs) {
        _numerator *= rhs._numerator;
        _denumerator *= rhs._denumerator;

        return this->Simplify();
    }

    Fraction & operator /= (CRef rhs) {
        if (rhs._numerator == NumberConstraint<T>::Zero) {
            throw std::runtime_error("Division by zero");
        }

        _numerator *= rhs._denumerator;
        _denumerator *= rhs._numerator;

        return this->Simplify();
    }

    Fraction operator -() const {
        return Fraction(-_numerator, _denumerator);
    }

    T Compare(CRef rhs) const {
        if (_denumerator == rhs._denumerator) {
            return _numerator - rhs._numerator;
        }

        auto number = Lcm(_denumerator, rhs._denumerator);
        return this->Multiply(number) - rhs.Multiply(number);
    }

    std::string ToString() const {
        std::stringstream stream;
        if (_numerator == _denumerator) return to_string(_numerator);

        stream << _numerator << "/"
            << _denumerator;

        return stream.str();
    }

private:
    static T Lcm(T left, T right) {
        return left * (right / Gcd(left, right));
    }

    static T Gcd(T left, T right) {
        return left ? Gcd(right % left, left) : right;
    }

    inline T Multiply(T number) const {
        return (number / _denumerator) * _numerator;
    }

    Fraction<T> & Simplify() {
        auto d = Gcd(::abs(_numerator), _denumerator);

        _numerator /= d;
        _denumerator /= d;

        return *this;
    }

    Fraction Multiplied(T number) const {
        return Fraction(this->Multiply(number), number);
    }

private:
    T _numerator;
    T _denumerator;
};

template<typename T, typename Stream>
Stream & operator << (Stream & stream, const Fraction<T> & rhs) {
    stream << rhs.ToString();

    return stream;
}

template<typename T, typename Stream>
Stream & operator >> (Stream & stream, Fraction<T> & rhs) {
    T denominator, numerator;
    char c;
    stream >> numerator >> c >> denominator;
    rhs = Fraction<T>(numerator, denominator);

    return stream;
}


template <typename T>
Fraction<T> operator+ (const Fraction<T> & left, const Fraction<T> & right) {
    auto tmp = left;
    return tmp += right;
}

template <typename T>
Fraction<T> operator- (const Fraction<T> & left, const Fraction<T> & right) {
    auto tmp = left;
    return tmp -= right;
}

template <typename T>
Fraction<T> operator* (const Fraction<T> & left, const Fraction<T> & right) {
    auto tmp = left;
    return tmp *= right;
}

template <typename T>
Fraction<T> operator/ (const Fraction<T> & left, const Fraction<T> & right) {
    auto tmp = left;
    return tmp /= right;
}

template <typename T>
bool operator==(const Fraction<T> & left, const Fraction<T> & right) {
    return left.Compare(right) == NumberConstraint<T>::Zero;
}

template <typename T>
bool operator!=(const Fraction<T> & left, const Fraction<T> & right) {
    return !(left == right);
}

template <typename T>
bool operator>(const Fraction<T> & left, const Fraction<T> & right) {
    return left.Compare(right) > NumberConstraint<T>::Zero;
}

template <typename T>
bool operator<(const Fraction<T> & left, const Fraction<T> & right) {
    return left.Compare(right) < NumberConstraint<T>::Zero;
}

template <typename T>
bool operator>=(const Fraction<T> & left, const Fraction<T> & right) {
    return !(left < right);
}

template <typename T>
bool operator<=(const Fraction<T> & left, const Fraction<T> & right) {
    return !(left > right);
}


#endif
