#ifndef PHONE_BOOK
#define PHONE_BOOK
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include "HashTable.h"
#include <list>

using namespace std;


class PhoneBook
{
    int maxUndos = 3;

    string menu[7] = {
        "1. Add record",
        "2. Change record",
        "3. Remove record",
        "4. Find record",
        "5. Undo",
        "6. Change max undos",
        "7. Exit"
    };

    enum Actions {
        Add = 1,
        Change,
        Remove,
        Find,
        Undo,
        MaxUndos,
        Exit
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
        string firstName, lastName, patronymic, email, work, post;
    };

    HashTable<string, BookRecord> records; 

    void printRecord(string phone, BookRecord rec);

    int modifiedCnt;

    struct LastAction {
        Actions action;
        string phone;
        BookRecord record;
    };

    int undos = maxUndos;

    list<LastAction> lastActions;
    void addLastAction(LastAction lastAct);

public:
    PhoneBook();


    void showMenu();
    void addRecord();
    void changeRecord();
    void removeRecord();
    void findRecord();
    void undo();
    void changeMaxUndos();

    bool handleCommand(int cmd);
    

    ~PhoneBook();
};



#endif // !PHONE_BOOK