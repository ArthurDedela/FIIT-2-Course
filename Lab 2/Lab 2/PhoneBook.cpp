#include "PhoneBook.h"



PhoneBook::PhoneBook()
{
    ifstream fin("bookdata.txt");

    if (!fin.is_open()) return;
      
    string number, s;

    while (!fin.eof()) {
        fin >> number;
        if (fin.eof()) break;
        fin >> s;
        records[number].firstName = s;
        fin >> s;
        records[number].lastName = s;
        fin >> s;
        records[number].patronymic = s;
        fin >> s;
        records[number].email = s;
        fin >> s;
        records[number].work = s;
        fin >> s;
        records[number].post = s;
    }

    fin.close();
}



void PhoneBook::addLastAction(LastAction lastAction)
{
    if (lastActions.size() == 10) {
        lastActions.pop_back();
    }
    undos = maxUndos;

    lastActions.push_front(lastAction);
}

void PhoneBook::printRecord(string phone, BookRecord rec)
{
    cout << "Phone: " << phone << '\n';
    cout << "First name: " << rec.firstName << '\n';
    cout << "Last name: " << rec.lastName << '\n';
    cout << "Patronymic: " << rec.patronymic << '\n';
    cout << "Email: " << rec.email << '\n';
    cout << "Work: " << rec.work << '\n';
    cout << "Post: " << rec.post << '\n';
}



void PhoneBook::showMenu()
{
    for (auto i : menu) {
        cout << i << '\n';
    }
    cout << ":: ";
}

void PhoneBook::addRecord()
{
    BookRecord rec;
    string phone;

    cout << "Phone: ";
    cin >> phone;
    if (records.find(phone)) {
        cout << "This phone already exist!\n";
        return;
    }

    cout << "First name: ";
    cin >> rec.firstName;
    cout << "Last name: ";
    cin >> rec.lastName;
    cout << "Patronymic: ";
    cin >> rec.patronymic;
    cout << "Email: ";
    cin >> rec.email;
    cout << "Work: ";
    cin >> rec.work;
    cout << "Post: ";
    cin >> rec.post;
    
    records[phone] = rec;

    cout << "Record added!\n";

    addLastAction(LastAction{ Add, phone, rec });
}

void PhoneBook::changeRecord()
{
    string phone;
    cout << "Enter phone: ";
    cin >> phone;

    cout << "What field you want to change?\n1. Phone 2. First name 3. Last name 4. Patronymic 5. Email 6. Work 7. Post\n:: ";
    int field;
    cin >> field;
    string input;
    cout << "Enter new information: ";
    cin >> input;

    BookRecord prevState = records[phone];

    switch (field) {
    case Phone:
        records[input] = records[phone];
        records.remove(phone);
        break;
    case FirstName:
        records[phone].firstName = input;
        break;
    case LastName:
        records[phone].lastName = input;
        break;
    case Patronymic:
        records[phone].patronymic = input;
        break;
    case Email:
        records[phone].email = input;
        break;
    case Work:
        records[phone].work = input;
        break;
    case Post:
        records[phone].post = input;
        break;
    default:
        cout << "Incorrect input!\n";
        return;
    }
    
    cout << "Record changed.\n";
    addLastAction(LastAction{ Change, phone, prevState });
}

void PhoneBook::removeRecord()
{
    string phone;

    cout << "Enter phone: ";
    cin >> phone;
    if (records.find(phone)) {
        addLastAction(LastAction{ Remove, phone, records[phone] });

        records.remove(phone);
        cout << "Record removed.\n";
        
    }
    else {
        cout << "Record not found.\n";
    }
    
}

void PhoneBook::findRecord()
{
    cout << "1. Phone 2. First name 3. Last name 4. Patronymic 5. Email 6. Work 7. Post\nEnter search criteria: ";
    int field, foundCnt = 1;
    string input;
    cin >> field;

    switch (field) {
    case Phone:
        cout << "Enter phone: ";
        cin >> input;
        for (auto it : records) {
            if (it.first.find(input) != string::npos) {
                cout << foundCnt++ << ") ";
                printRecord(it.first, it.second);
            }
        }

        if (foundCnt == 1) cout << "Nothing found.\n";

        break;
    case FirstName:
        cout << "Enter first name: ";
        cin >> input;

        for (auto it : records) {
            if (it.second.firstName.find(input) != string::npos) { 
                cout << foundCnt++ << ") ";
                printRecord(it.first, it.second);                
            }
        }

        if (foundCnt == 1) cout << "Nothing found.\n";

        break;
    case LastName:
        cout << "Enter last name: ";
        cin >> input;

        for (auto it : records) {
            if (it.second.lastName.find(input) != string::npos) {
                cout << foundCnt++ << ") ";
                printRecord(it.first, it.second);
            }
        }

        if (foundCnt == 1) cout << "Nothing found.\n";

        break;
    case Patronymic:
        cout << "Enter patrnonymic: ";
        cin >> input;

        for (auto it : records) {
            if (it.second.patronymic.find(input) != string::npos) {
                cout << foundCnt++ << ") ";
                printRecord(it.first, it.second);
            }
        }

        if (foundCnt == 1) cout << "Nothing found.\n";

        break;
    case Email:
        cout << "Enter email: ";
        cin >> input;

        for (auto it : records) {
            if (it.second.email.find(input) != string::npos) {
                cout << foundCnt++ << ") ";
                printRecord(it.first, it.second);
            }
        }

        if (foundCnt == 1) cout << "Nothing found.\n";

        break;
    case Work:
        cout << "Enter work: ";
        cin >> input;

        for (auto it : records) {
            if (it.second.work.find(input) != string::npos) {
                cout << foundCnt++ << ") ";
                printRecord(it.first, it.second);
            }
        }

        if (foundCnt == 1) cout << "Nothing found.\n";

        break;
    case Post:
        cout << "Enter post: ";
        cin >> input;

        for (auto it : records) {
            if (it.second.post.find(input) != string::npos) {
                cout << foundCnt++ << ") ";
                printRecord(it.first, it.second);
            }
        }

        if (foundCnt == 1) cout << "Nothing found.\n";

        break;
    default:
        cout << "Incorrect input!\n";
        return;
    }


}

void PhoneBook::undo()
{
    if (!undos) {
        cout << "You can't undo more times.\n";
        return;
    }
    if (lastActions.empty()) {
        cout << "No actions in history.\n";
        return;
    }
    auto lastAction = lastActions.front();

    lastActions.pop_front();
    switch (lastAction.action) {
    case Add:
        records.remove(lastAction.phone);
        break;
    case Change:
    case Remove:
        records[lastAction.phone] = lastAction.record;
        break;
    default:
        return;
    }
    undos--;

    cout << "Cancelled last action.\n";
}

void PhoneBook::changeMaxUndos()
{
    cout << "Enter max undos: ";
    unsigned max;
    cin >> max;
    undos = maxUndos = max;
}

bool PhoneBook::handleCommand(int cmd)
{
    switch (cmd) {
    case Add:
        addRecord();
        return true;
    case Change:
        changeRecord();
        return true;
    case Remove:
        removeRecord();
        return true;
    case Find:
        findRecord();
        return true;
    case Undo:
        undo();
        return true;
    case MaxUndos:
        changeMaxUndos();
        return true;
    case Exit:
        return true;
    default:
        return false;
    }
}



PhoneBook::~PhoneBook()
{
    ofstream fout("bookdata.txt");

    for (auto it : records) {
        fout << it.first << ' ' << it.second.firstName << ' ' << it.second.lastName << ' ' << it.second.patronymic << ' ' << it.second.email << ' ' << it.second.work << ' ' << it.second.post << '\n';
    }

    fout.close();
}
