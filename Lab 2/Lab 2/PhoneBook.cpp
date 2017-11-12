#include "PhoneBook.h"



PhoneBook::PhoneBook()
{
    ifstream fin("bookdata.txt");
    if (!fin.is_open()) return;
    
    string numbers, s;
    

    while (!fin.eof()) {
        BookRecord rec;
        unsigned index = records.size();

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

        hash_lastName[rec.lastName].push_back(index);
        for (auto it : rec.phone_numbers) {
            hash_phone[it] = index;
        }

        records.push_back(rec);
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
    unsigned index = records.size();

    cout << "Enter phone numbers or \"STOP\" to finish:\n";
    while (true) {   
        cout << ":: ";
        cin >> phone;

        if (phone == "STOP") break;

        if (hash_phone.find(phone)) {
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
        hash_phone[it] = index;
    }
    hash_lastName[rec.lastName].push_back(index);

    records.push_back(rec);

    cout << "Record added!\n";

    addLastAction(LastAction{ Add, rec, index });
}

void PhoneBook::changeRecord()
{
    string phone;
    cout << "Enter phone: ";
    cin >> phone;

    if (!hash_phone.find(phone)) {
        cout << "Contact not found!\n";
        return;
    }
    unsigned i = hash_phone[phone];
    printRecord(records[i]);

    cout << "What field you want to change?\n1. Phone 2. First name 3. Last name 4. Patronymic 5. Email 6. Work 7. Post\n";
    int field;
    field = _getch() - '0';

    string input;
    
    BookRecord prevState = records[i];
    BookRecord & nextState = records[i];

    switch (field) {
    case Phone:
        for (auto it : nextState.phone_numbers) {
            hash_phone.remove(it);
        }
        nextState.phone_numbers.clear();

        cout << "Enter phone numbers or \"STOP\" to finish: ";
        while (true) {
            string phone;
            cout << ":: ";
            cin >> phone;

            if (phone == "STOP") break;

            if (hash_phone.find(phone)) {
                cout << "This phone number already exist!\n";
                continue;
            }

            if (phone.length() > 0) nextState.phone_numbers.push_back(phone);
        }

        for (auto it : nextState.phone_numbers) {
            hash_phone[it] = i;
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

        for (auto it = hash_lastName[nextState.lastName].begin(); it != hash_lastName[nextState.lastName].end(); ++it) {
            if (*it == i) {
                hash_lastName[nextState.lastName].erase(it);
                break;
            }
        }
        nextState.lastName = input;

        hash_lastName[nextState.lastName].push_back(i);
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
    if (hash_phone.find(phone)) {        
        unsigned i = hash_phone[phone];

        for (auto it : records[i].phone_numbers) {
            hash_phone.remove(it);
        }
        for (auto it = hash_lastName[records[i].lastName].begin(); it != hash_lastName[records[i].lastName].end(); ++it) {
            if (*it == i) {
                hash_lastName[records[i].lastName].erase(it);
                break;
            }
        }
        
        addLastAction(LastAction{ Remove, records[i], i });

        records[i] = BookRecord();
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
        
        if (hash_phone.find(input)) {
            printRecord(records[hash_phone[input]]);
            foundCnt = 1;
        }   

        break;
    case FirstName:
        cout << "Enter first name: ";
        cin >> input;

        for (auto it : records) {
            if (it.firstName == input) { 
                cout << ++foundCnt << ") ";
                printRecord(it);                
            }
        }

        break;
    case LastName:
        cout << "Enter last name: ";
        cin >> input;

        if (hash_lastName.find(input)) {
            for (auto it : hash_lastName[input]) {
                cout << ++foundCnt << ") ";
                printRecord(records[it]);
            }
        }

        break;
    case Patronymic:
        cout << "Enter patrnonymic: ";
        cin >> input;

        for (auto it : records) {
            if (it.patronymic == input) {
                cout << ++foundCnt << ") ";
                printRecord(it);
            }
        }

        break;
    case Email:
        cout << "Enter email: ";
        cin >> input;

        for (auto it : records) {
            if (it.email == input) {
                cout << ++foundCnt << ") ";
                printRecord(it);
            }
        }

        break;
    case Work:
        cout << "Enter work: ";
        cin >> input;

        for (auto it : records) {
            if (it.work == input) {
                cout << ++foundCnt << ") ";
                printRecord(it);
            }
        }

        break;
    case Post:
        cout << "Enter post: ";
        cin >> input;

        for (auto it : records) {
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

    for (auto it : records) {
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
    int i = lastAction.index;

    switch (lastAction.action) {
    case Add:
        records.erase(records.begin() + i);
        for (auto it : lastAction.record.phone_numbers) {
            hash_phone.remove(it);
        }
        break;

    case Change:        
        for (auto it : records[i].phone_numbers) {
            hash_phone.remove(it);
        }
        for (auto it = hash_lastName[records[i].lastName].begin(); it != hash_lastName[records[i].lastName].end(); ++it) {
            if (*it == i) {
                hash_lastName[records[i].lastName].erase(it);
                break;
            }
        }

        records[i] = lastAction.record;

        for (auto it : records[i].phone_numbers) {
            hash_phone[it] = i;
        }
        hash_lastName[records[i].lastName].push_back(i);

        break;

    case Remove:
        records[i] = lastAction.record;
        for (auto it : records[i].phone_numbers) {
            hash_phone[it] = i;
        }
        hash_lastName[records[i].lastName].push_back(i);
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

void PhoneBook::showAll()
{
    for (auto it : records) {
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

    for (auto it : records) {
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