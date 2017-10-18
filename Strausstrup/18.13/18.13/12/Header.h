#pragma once
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <bitset>


using namespace std;

namespace ArturDedela {

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

    int task9() {
        AND<int> and;
        OR<int> or ;
        OR<bitset<5>> or_set;
        XOR<int> xor;
        XOR<char> xor_char;

        bitset<5> a;
        bitset<5> b = 3;

        cout << or_set(a, b) << '\n';
        cout << xor_char('1', '2') << '\n';

        cout << and (7, 13) << '\n';
        cout << or (1, 2) << '\n';
        cout << xor (2, 4) << '\n';


        system("pause");
        return 0;
    }

    int task8() {
        vector<int> squares;
        squares.resize(100);

        cout << "Squares: ";
        for (int i = 1; i <= 100; i++) {
            cout << (squares[i - 1] = i*i) << ' ';
        }
        cout << '\n';
        cout << "Square root: ";
        for (auto it : squares) {
            cout << sqrt(it) << ' ';
        }
        cout << '\n';

        system("pause");

        return 0;
    }

    int task11() {

        ifstream fin("ArturDedela11.txt");
        if (!fin.is_open()) {
            throw std::runtime_error("Can't open file.");
        }

        string input, prev("");
        string buf;

        while (!fin.eof()) {
            fin >> input;

            if (input != prev) {
                buf += input + ' ';
            }

            prev = input;
        }
        ofstream fout("ArturDedela11.txt", ios_base::out);
        fout << buf;

        system("pause");
        return 0;
    }

    int task15() {

        cout << "Enter sentence: " << '\n';
        string sentence;
        getline(cin, sentence);

        stringstream ss(sentence);
        vector<string> words;
        string word;

        while (ss >> word) words.push_back(word);

        sort(words.begin(), words.end());
        while (next_permutation(words.begin(), words.end()))
        {
            for (auto & it : words) {
                cout << it << " ";
            }
            cout << '\n';
        }

        system("pause");

        return 0;
    }

}