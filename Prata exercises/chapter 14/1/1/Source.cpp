#include <iostream>
#include "Wine.h"


int main() {
    string wineName;
    unsigned y;
    cout << "Enter name of wine: ";
    getline(cin, wineName);
    cout << "Enter number of years: ";
    cin >> y;

    Wine wine(wineName, y);
    wine.GetBottles();

    wine.show();

    cout << "Wine label: " << wine.label() << '\n';
    cout << "Total bottles: " << wine.sum() << '\n';

    system("pause");
    return 0;
}