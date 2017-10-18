#include <map>
#include <sstream>
#include <string>




template <typename T>
class Polynom
{
    std::map<int, T> monoms;

public:
    Polynom() {}

    Polynom(const std::string & s) {
        istringstream iss(s);
        T coef;
        char x;
        int power;

        while (!iss.eof()) {
            iss >> coef >> x >> x >> power;
            monoms[power] += coef;
        }
    }

    void addMonom(T & coef, int power) {
        monoms[power] += coef;
        if (monoms[power] == T{}) {
            monoms.erase(power);
        }
    }


    Polynom & operator+=(const Polynom & pol) {
        for (auto  it : pol.monoms) {
            this->addMonom(it.second, it.first);
        }

        return *this;
    }

    Polynom operator-() const {
        auto tmp = *this;
        for (auto & it : tmp.monoms) {
            it.second = -it.second;
        }

        return tmp;
    }

    Polynom & operator-=(const Polynom & pol) {
        return *this += -pol;
    }

    Polynom & operator*=(const Polynom & pol) {
        Polynom<T> tmp;

        for (auto & it_1 : monoms) {
            for (auto & it_2 : pol.monoms) {
                tmp.addMonom(it_1.second * it_2.second, it_1.first + it_2.first);
            }
        }

        return *this = tmp;
    }

    Polynom & operator/=(const Polynom & pol) {
        Polynom<T> result, remainder;
        divide(pol, result, remainder);
        *this = result;
        clear();
        return *this;
    }

    Polynom & operator%=(const Polynom & pol)
    {
        Polynom<T> result, remainder;
        divide(pol, result, remainder);
        *this = remainder;
        clear();
        return *this;
    }

    std::pair<int, T> getMaxMonom() {
        std::pair<int, T> last;

        for (auto a : monoms) last = a;

        return last;
    }

    void divide(Polynom pol, Polynom & result, Polynom & remainder) {
        remainder = *this;
        auto max_mon_this = remainder.getMaxMonom();
        auto max_mon_pol = pol.getMaxMonom();
        T zero{};

        while (max_mon_this.first >= max_mon_pol.first) {

            if (max_mon_pol.second == zero) {
                throw std::runtime_error("division by zero");
            }

            max_mon_this.first -= max_mon_pol.first;
            max_mon_this.second /= max_mon_pol.second;

            if (max_mon_this.second == zero) {
                break;
            }

            result.addMonom(max_mon_this.second, max_mon_this.first);

            Polynom<T> tmp_poly;
            tmp_poly.addMonom(max_mon_this.second, max_mon_this.first);

            tmp_poly *= pol;
            remainder -= tmp_poly;

            remainder.clear();
            max_mon_this = remainder.getMaxMonom();
        }
    }

    Polynom derivative() const
    {
        Polynom<T> tmp;
        T zero{};
        for (auto it : this->monoms) {
            if (it.first > 0) {
                T h(it.first);
                tmp.addMonom(it.second * h, it.first - 1);
            }
        }
        return tmp;
    }

    Polynom superposition(const Polynom & pol) const {
        Polynom<T> res, tmp, mon;
        T zero{};

        for (auto & it : this->monoms) {
            tmp.monoms.clear();
            mon.monoms.clear();
            mon.addMonom(it.second, 0);

            if (it.first > 0) {
                tmp = pol;
                for (unsigned i = 1; i < it.first; i++)
                    tmp *= pol;

                mon *= tmp;
                res += mon;
            }
            else {
                res += mon;
            }
        }

        return res;
    }

    void clear()
    {
        T zero{};
        std::map<int, T> tmp;
        for (auto & it : monoms) {
            if (it.first >= 0 && it.second != zero) {
                tmp[it.first] = it.second;
            }
        }
        monoms = tmp;
    }

    std::string toStr() const {
        std::ostringstream oss;
        oss << "<";
        if (monoms.size() == 0) oss << 0;
        for (auto & it : monoms) {
            oss << ' ';
            oss.setf(ios_base::showpos);
            oss << it.second << "x^";
            oss.unsetf(ios_base::showpos);
            oss << it.first << ' ';
        }
        oss << ">";

        return oss.str();
    }

};

template <typename Stream, typename T>
Stream & operator<<(Stream & os, const Polynom<T> & pol) {
    os << pol.toStr();
    return os;
}

template <typename T>
Polynom<T> operator+(const Polynom<T> & pol, const Polynom<T> & pol_2) {
    Polynom<T> tmp{ pol };
    tmp += pol_2;
    return tmp;
}

template <typename T>
Polynom<T> operator-(const Polynom<T> & pol, const Polynom<T> & pol_2) {
    Polynom<T> tmp{ pol };
    tmp -= pol_2;
    return tmp;
}

template <typename T>
Polynom<T> operator*(const Polynom<T> & pol, const Polynom<T> & pol_2) {
    Polynom<T> tmp{ pol };
    tmp *= pol_2;
    return tmp;
}

template <typename T>
Polynom<T> operator/(Polynom<T> & pol, Polynom<T> & pol_2) {
    Polynom<T> tmp{ pol };
    tmp /= pol_2;
    return tmp;
}

template <typename T>
Polynom<T> operator%(Polynom<T> & pol, Polynom<T> & pol_2) {
    Polynom<T> tmp{ pol };
    tmp %= pol_2;
    return tmp;
}

