#include <iostream>
#include <string>
#include <conio.h>
#include "PhoneBook.h"


using namespace std;

int main() {

    PhoneBook book;

    int cmd;
    do {
        book.showMenu();
        cmd = _getch() - '0';
        if (!book.handleCommand(cmd)) {
            cout << "Incorrect input!\n";
        }
    } while (cmd != Exit);

    return 0;
}