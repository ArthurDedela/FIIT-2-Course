#pragma once
#include <iostream>
#include <string>
#include <valarray>

using namespace std;


class Wine
{
    string _label;
    pair<valarray<int>, valarray<int>> Pair;
    unsigned productionYears = 0;

public:

    Wine();
    Wine(const string & label, unsigned y, const int years[], const int bottles[]);
    Wine(const string & label, unsigned y);

    void GetBottles();

    string & label() { return _label; }

    unsigned sum() { return Pair.second.sum(); }

    void show();


    ~Wine();
};
