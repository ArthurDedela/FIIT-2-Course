#include "Wine.h"

Wine::Wine()
{
}

Wine::Wine(const string & label, unsigned y)
{
    _label = label;
    productionYears = y;
    Pair.first.resize(y);
    Pair.second.resize(y);
}

void Wine::GetBottles()
{
    cout << "Enter " << _label << " data for " << productionYears << " year(s)\n";
    for (int i = 0; i < productionYears; i++) {
        cout << "Enter year: ";
        cin >> Pair.first[i];
        cout << "Enter the number of bottles produced: ";
        cin >> Pair.second[i];
    }
}

Wine::Wine(const string & label, unsigned y, const int years[], const int bottles[]) : Wine(label, y)
{    
    for (int i = 0; i < y; i++) {
        Pair.first[i] = years[i];
        Pair.second[i] = bottles[i];
    }
}

void Wine::show()
{
    cout << "Wine: " << _label << '\n';
    cout << "Year | Bottles\n";
    for (int i = 0; i < productionYears; i++) {
        cout << Pair.first[i] << "   " << Pair.second[i] << '\n';
    }
}

Wine::~Wine()
{
}
