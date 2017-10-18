#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include "Header.h"

/*
ќпределите формат записи дл€ ссылок на статьи и книги. 
Ќапишите программу, котора€ могла бы выбирать из файла записи по времени издани€, имени автора, издательству или ключевам словам. 
ѕользователь должен иметь возможность указать один из этих критериев дл€ сортировки выхода.
*/

using namespace std;



int main() {

    ArturDedela::task8();
    ArturDedela::task9();
    ArturDedela::task11();
    ArturDedela::task15();


 /*   Record rec{ "12:24", "Artur", "Publisher", {"Kniga", "Top", "LALA"} };

    Library lib("db.txt");

    cout << "1) Publish time\n2) Author\n3) Publisher\n4) Keywords\n 5) Exit\n";

    string input;
        
    while (true) {        
        cout << "Get records by: ";
        int searchBy, sortBy;
        cin >> searchBy;
        if (searchBy == 5) break;

        cin >> input;
        
        cout << "Sort records by: ";
        cin >> sortBy;

        if (sortBy < 1 || sortBy > 4 || searchBy < 1 || searchBy > 4) {
            cout << "Incorrect input!\n";
            continue;
        }

        lib.getRecords(searchBy, sortBy);
    }*/


    system("pause");
    return 0;
}