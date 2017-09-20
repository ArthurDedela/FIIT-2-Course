#pragma once
#include "Person.h"
#include <ctime>
#include <string>

class PokerPlayer : virtual public Person
{

public:
    PokerPlayer(string fn, string ln) : Person(fn, ln) {};

    int Draw() {
        srand(time(NULL));
        return rand() % 52 + 1;
    }

    void Show() {
        Person::Show();
        cout << "Card: " << Draw() << '\n';
    }

};

