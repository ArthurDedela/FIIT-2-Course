#pragma once
#include "Person.h"
#include <iostream>
#include <string>

class Gunslinger : virtual public Person
{
    double prepTime;
    int scratches = 3;

public:
    Gunslinger(string firstName, string lastName, double prepareTime, int scratches) : Person(firstName, lastName), prepTime(prepareTime), scratches(scratches) {};

    double Draw() { return prepTime; }

    void Show() {
        Person::Show();
        cout << "Prepare time: " << prepTime << '\n' << "Scratches: " << scratches << '\n';
    }

};

