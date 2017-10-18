#include <iostream>
#include <string>
#include "HashTable.h"
#include "PhoneBook.h"

using namespace std;

int main() {

    PhoneBook book;
 
    int cmd;
    do {
        book.showMenu();
        cin >> cmd;
        if (!book.handleCommand(cmd)) {
            cout << "Incorrect input!\n";
        }
    } while (cmd != 7);

    return 0;
}