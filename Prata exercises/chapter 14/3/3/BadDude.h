#pragma once
#include "PokerPlayer.h"
#include "Gunslinger.h"

class BadDude : public PokerPlayer, public Gunslinger
{

public:
    BadDude(string fn, string ln, double gunTime) : PokerPlayer(fn, ln), Gunslinger(fn, ln, gunTime, 5), Person(fn, ln) {};

    double GDraw() {
        return Gunslinger::Draw();
    }

    int CDraw() {
        return PokerPlayer::Draw();
    }

    void Show() {
        Gunslinger::Show();
        cout << "Card: " << CDraw() << '\n';
    }
};

