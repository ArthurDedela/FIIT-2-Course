#ifndef PHONE_BOOK
#define PHONE_BOOK

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <functional>
#include "HashTable.h"
#include <conio.h>
#include <list>

using namespace std;

enum Actions {
    Add = 1,
    Change,
    Remove,
    Find,
    Undo,
    ShowAll,
    MaxUndos,
    Save,
    Exit
};

class PhoneBook
{
    string menu[9] = {
        "1. Add record",
        "2. Change record",
        "3. Remove record",
        "4. Find record",
        "5. Undo",
        "6. Show all",
        "7. Change max undos",
        "8. Save",
        "9. Exit"
    };    

    enum Fields {
        Phone = 1,
        FirstName,
        LastName,
        Patronymic,
        Email,
        Work,
        Post
    };

    struct BookRecord {
        vector<string> phone_numbers;
        string firstName, lastName, patronymic, email, work, post;
    };

    unsigned _rec_cnt = 0;
    vector<BookRecord> _records;

    HashTable<string, int> _hash_phone;
    HashTable<string, vector<int>> _hash_lastName;


    struct LastAction {
        Actions action;
        BookRecord record;
        unsigned index;
    };

    int _modifiedCnt;

    int _maxUndos = 3;
    int _undos = _maxUndos;

    list<LastAction> _lastActions;
    void addLastAction(LastAction lastAct);

    void printRecord(const BookRecord & rec);
    void saveBook();

public:
    PhoneBook();


    void showMenu();
    void addRecord();
    void changeRecord();
    void removeRecord();
    void findRecord();
    void findByPart();
    void undo();
    void changeMaxUndos();
    void showAll();

    bool handleCommand(int cmd);
    

    ~PhoneBook();
};



#endif // !PHONE_BOOK