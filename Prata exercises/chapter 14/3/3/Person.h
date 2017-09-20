#pragma once
#include <iostream>
#include <string>

using namespace std;

class Person
{
    string fName, lName;

public:
    //Person() {};
    Person(string firstName, string lastName) : fName(firstName), lName(lastName) {};

    void Show() {
        cout << fName << ' ' << lName << '\n';
    }
};

