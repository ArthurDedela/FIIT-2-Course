#include "PhoneBook.h"



PhoneBook::PhoneBook()
{
    ifstream fin("bookdata.txt");
    if (!fin.is_open()) return;
    
    string numbers, s;
    
    while (!fin.eof()) {
        BookRecord rec;
        unsigned index = _records.size();

        getline(fin, numbers);
        if (numbers.length() == 0) break;

        istringstream iss(numbers);
        copy(istream_iterator<string>(iss),
            istream_iterator<string>(),
            back_inserter(rec.phone_numbers)
        );        

        getline(fin, s);
        istringstream iss2(s);

        iss2 >> rec.firstName
            >> rec.lastName 
            >> rec.patronymic 
            >> rec.email 
            >> rec.work 
            >> rec.post;

        _hash_lastName[rec.lastName].push_back(index);
        for (auto it : rec.phone_numbers) {
            _hash_phone[it] = index;
        }

        _records.push_back(rec);
    }

    fin.close();
}



void PhoneBook::addLastAction(LastAction lastAction)
{
    if (_lastActions.size() == MaxUndos) {
        _lastActions.pop_back();
    }
    _undos = _maxUndos;

    _lastActions.push_front(lastAction);
}

void PhoneBook::printRecord(const BookRecord & rec)
{
    cout << "**************************\n";
    cout << "Last name: " << rec.lastName << '\n';
    cout << "First name: " << rec.firstName << '\n';    
    cout << "Patronymic: " << rec.patronymic << '\n';
    cout << "Phone numbers: \n";
    for (auto it : rec.phone_numbers) {
        cout << '\t' << it << '\n';
    }
    cout << "Email: " << rec.email << '\n';
    cout << "Work: " << rec.work << '\n';
    cout << "Post: " << rec.post << '\n';
    cout << "**************************\n";
}



void PhoneBook::showMenu()
{
    cout << "/~~~~~~~~~~~~~~~~~~~~\\\n";
    for (auto i : menu) {
        cout << i << '\n';
    }
}

void PhoneBook::addRecord()
{
    BookRecord rec;
    string phone;
    unsigned index = _records.size();

    cout << "Enter phone numbers or \"STOP\" to finish:\n";
    while (true) {   
        cout << ":: ";
        cin >> phone;

        if (phone == "STOP") break;

        if (_hash_phone.find(phone)) {
            cout << "This phone number already exist!\n";
            continue;
        }

        if (phone.length() > 0) rec.phone_numbers.push_back(phone);
    }

    if (rec.phone_numbers.size() == 0) {
        cout << "Contact not created. You must enter at least one phone number!\n";
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
    
    
    for (auto it : rec.phone_numbers) {
        _hash_phone[it] = index;
    }
    _hash_lastName[rec.lastName].push_back(index);

    _records.push_back(rec);

    cout << "Record added!\n";

    addLastAction(LastAction{ Add, rec, index });
}

void PhoneBook::changeRecord()
{
    string phone;
    cout << "Enter phone: ";
    cin >> phone;

    if (!_hash_phone.find(phone)) {
        cout << "Contact not found!\n";
        return;
    }
    unsigned i = _hash_phone[phone];
    printRecord(_records[i]);

    cout << "What field you want to change?\n1. Phone 2. First name 3. Last name 4. Patronymic 5. Email 6. Work 7. Post\n";
    int field;
    field = _getch() - '0';

    string input;
    
    BookRecord prevState = _records[i];
    BookRecord & nextState = _records[i];

    switch (field) {
    case Phone:
        for (auto it : nextState.phone_numbers) {
            _hash_phone.remove(it);
        }
        nextState.phone_numbers.clear();

        cout << "Enter phone numbers or \"STOP\" to finish: \n";
        while (true) {
            string phone;
            cout << ":: ";
            cin >> phone;

            if (phone == "STOP") break;

            if (_hash_phone.find(phone)) {
                cout << "This phone number already exist!\n";
                continue;
            }

            if (phone.length() > 0) nextState.phone_numbers.push_back(phone);
        }

        for (auto it : nextState.phone_numbers) {
            _hash_phone[it] = i;
        }

        break;
    case FirstName:
        cout << "Enter new first name: ";
        cin >> input;
        nextState.firstName = input;
        break;
    case LastName:
        cout << "Enter new last name: ";
        cin >> input;

        for (auto it = _hash_lastName[nextState.lastName].begin(); it != _hash_lastName[nextState.lastName].end(); ++it) {
            if (*it == i) {
                _hash_lastName[nextState.lastName].erase(it);
                break;
            }
        }
        nextState.lastName = input;

        _hash_lastName[nextState.lastName].push_back(i);
        break;
    case Patronymic:
        cout << "Enter new patronymic: ";
        cin >> input;
        nextState.patronymic = input;
        break;
    case Email:
        cout << "Enter new email: ";
        cin >> input;
        nextState.email = input;
        break;
    case Work:
        cout << "Enter new work: ";
        cin >> input;
        nextState.work = input;
        break;
    case Post:
        cout << "Enter new post: ";
        cin >> input;
        nextState.post = input;
        break;
    default:
        cout << "Incorrect input!\n";
        return;
    }
    
    cout << "Record changed.\n";
    addLastAction(LastAction{ Change, prevState, i });
}

void PhoneBook::removeRecord()
{
    string phone;

    cout << "Enter phone: ";
    cin >> phone;
    if (_hash_phone.find(phone)) {        
        unsigned i = _hash_phone[phone];

        for (auto it : _records[i].phone_numbers) {
            _hash_phone.remove(it);
        }
        for (auto it = _hash_lastName[_records[i].lastName].begin(); it != _hash_lastName[_records[i].lastName].end(); ++it) {
            if (*it == i) {
                _hash_lastName[_records[i].lastName].erase(it);
                break;
            }
        }
        
        addLastAction(LastAction{ Remove, _records[i], i });

        _records[i] = BookRecord();
        cout << "Record removed.\n";        
    }
    else {
        cout << "Record not found.\n";
    }
    
}

void PhoneBook::findRecord()
{
    cout << "\n1. Phone 2. First name 3. Last name 4. Patronymic 5. Email 6. Work 7. Post\n";
    int field, foundCnt = 0;
    string input;
    field = _getch() - '0';

    switch (field) {
    case Phone:
        cout << "Enter phone: ";
        cin >> input;
        
        if (_hash_phone.find(input)) {
            printRecord(_records[_hash_phone[input]]);
            foundCnt = 1;
        }   

        break;
    case FirstName:
        cout << "Enter first name: ";
        cin >> input;

        for (auto it : _records) {
            if (it.firstName == input) { 
                cout << ++foundCnt << ") ";
                printRecord(it);                
            }
        }

        break;
    case LastName:
        cout << "Enter last name: ";
        cin >> input;

        if (_hash_lastName.find(input)) {
            for (auto it : _hash_lastName[input]) {
                cout << ++foundCnt << ") ";
                printRecord(_records[it]);
            }
        }

        break;
    case Patronymic:
        cout << "Enter patrnonymic: ";
        cin >> input;

        for (auto it : _records) {
            if (it.patronymic == input) {
                cout << ++foundCnt << ") ";
                printRecord(it);
            }
        }

        break;
    case Email:
        cout << "Enter email: ";
        cin >> input;

        for (auto it : _records) {
            if (it.email == input) {
                cout << ++foundCnt << ") ";
                printRecord(it);
            }
        }

        break;
    case Work:
        cout << "Enter work: ";
        cin >> input;

        for (auto it : _records) {
            if (it.work == input) {
                cout << ++foundCnt << ") ";
                printRecord(it);
            }
        }

        break;
    case Post:
        cout << "Enter post: ";
        cin >> input;

        for (auto it : _records) {
            if (it.post == input) {
                cout << ++foundCnt << ") ";
                printRecord(it);
            }
        }

        break;
    default:
        cout << "Incorrect input!\n";
        return;
    }

    if (foundCnt == 0) {
        cout << "Nothing found.\nDo you want to try find by part (Y/N)?\n";
        char c = toupper(_getch());
        if (c == 'Y') {
            findByPart();
        }
    }
}

void PhoneBook::findByPart()
{
    cout << "\n1. Phone 2. First name 3. Last name 4. Patronymic 5. Email 6. Work 7. Post\n";
    int field, foundCnt = 0;
    string input;
    field = _getch() - '0';
    cout << "Enter search request: ";
    cin >> input;

    for (auto it : _records) {
        switch (field)
        {
        case Phone:
            for (auto number : it.phone_numbers) {
                if (number.find(input) != string::npos) {
                    printRecord(it);
                    return;
                }
            }
            break;

        case FirstName:
            if (it.firstName.find(input) != string::npos) {
                cout << ++foundCnt;
                printRecord(it);
            }
            break;

        case LastName:
            if (it.lastName.find(input) != string::npos) {
                cout << ++foundCnt;
                printRecord(it);
            }
            break;

        case Patronymic:
            if (it.patronymic.find(input) != string::npos) {
                cout << ++foundCnt;
                printRecord(it);
            }
            break;

        case Email:
            if (it.email.find(input) != string::npos) {
                cout << ++foundCnt;
                printRecord(it);
            }
            break;

        case Work:
            if (it.work.find(input) != string::npos) {
                cout << ++foundCnt;
                printRecord(it);
            }
            break;

        case Post:
            if (it.post.find(input) != string::npos) {
                cout << ++foundCnt;
                printRecord(it);
            }
            break;

        default:
            break;
        }
    }
}

void PhoneBook::undo()
{
    if (!_undos) {
        cout << "You can't undo more times.\n";
        return;
    }
    if (_lastActions.empty()) {
        cout << "No actions in history.\n";
        return;
    }
    auto lastAction = _lastActions.front();

    _lastActions.pop_front();
    int i = lastAction.index;

    switch (lastAction.action) {
    case Add:
        _records.erase(_records.begin() + i);
        for (auto it : lastAction.record.phone_numbers) {
            _hash_phone.remove(it);
        }
        break;

    case Change:        
        for (auto it : _records[i].phone_numbers) {
            _hash_phone.remove(it);
        }
        for (auto it = _hash_lastName[_records[i].lastName].begin(); it != _hash_lastName[_records[i].lastName].end(); ++it) {
            if (*it == i) {
                _hash_lastName[_records[i].lastName].erase(it);
                break;
            }
        }

        _records[i] = lastAction.record;

        for (auto it : _records[i].phone_numbers) {
            _hash_phone[it] = i;
        }
        _hash_lastName[_records[i].lastName].push_back(i);

        break;

    case Remove:
        _records[i] = lastAction.record;
        for (auto it : _records[i].phone_numbers) {
            _hash_phone[it] = i;
        }
        _hash_lastName[_records[i].lastName].push_back(i);
        break;
    default:
        return;
    }
    _undos--;

    cout << "Cancelled last action.\n";
}

void PhoneBook::changeMaxUndos()
{
    cout << "Enter max undos: ";
    unsigned max;
    cin >> max;
    _undos = _maxUndos = max;
}

void PhoneBook::showAll()
{
    for (auto it : _records) {
        if (it.phone_numbers.size())
            printRecord(it);
    }
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
    case ShowAll:
        showAll();
        return true;
    case MaxUndos:
        changeMaxUndos();
        return true;
    case Save:
        saveBook();
        return true;
    case Exit:
        return true;
    default:
        return false;
    }
}

void PhoneBook::saveBook() {
    ofstream fout("bookdata.txt");

    for (auto it : _records) {
        if (it.phone_numbers.size() == 0) continue;
        for (auto number : it.phone_numbers) {
            fout << number << " ";
        }
        fout << '\n';
        fout << it.firstName << " " << it.lastName << " " << it.patronymic << " " << it.email << " " << it.work << " " << it.post << '\n';
    }

    fout.close();
}

PhoneBook::~PhoneBook()
{
    saveBook();
}