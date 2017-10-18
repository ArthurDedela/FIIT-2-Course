#include <iostream>
#include <bitset>

using namespace std;

template <typename T>
class AND {
public:
    T operator()(const T & a, const T & b) {
        return a & b;
    }
};

template <typename T>
class OR {
public:
    T operator()(const T & a, const T & b) {
        return a | b;
    }
};

template <typename T>
class XOR {
public:
    T operator()(const T & a, const T & b) {
        return a ^ b;
    }
};



int main() {
    AND<int> and;    
    OR<int> or;
    OR<bitset<5>> or_set ;
    XOR<int> xor;
    XOR<char> xor_char;

    bitset<5> a;
    bitset<5> b = 3;

    cout << or_set (a, b) << '\n';
    cout << xor_char('1', '2') << '\n';

    cout << and (7, 13) << '\n';
    cout << or (1, 2) << '\n';
    cout << xor (2, 4) << '\n';    


    system("pause");
    return 0;
}