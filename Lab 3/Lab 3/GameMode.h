#ifndef _GAMEMODE
#define _GAMEMODE

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <conio.h>
#include <mutex>
#include <sstream>
#include "Hero.h"
#include "HeroFactory.h"

using namespace std;


class GameMode
{
public:
    enum MainMenu {
        Fight = 1,
        Inventory,
        Abilities,
        ChangeHero,
        Exit
    };

    enum FightMenu {
        Attack = 1,
        Ability1,
        Ability2
    };

private:
    //vector<Item> items;
    const vector<string> _mainmenu = {
        "Fight",
        "Inventory",
        "Abilities",
        "Change hero",        
        "Exit"
    };
    
    HeroFactory _heroFactory;
    shared_ptr<Hero> _hero;
    bool _heroDied = false;
    
    vector<Item> _items;

    const HANDLE _Console = GetStdHandle(STD_OUTPUT_HANDLE);
    mutex _consoleMutex;

    bool _fighting;

private:
    void chooseHero() {
        int i = 1;
        cout << "Choose your hero:\n";
        for (auto it : HeroNames) {
            cout << i++ << ". " << it << '\n';
        }

        int choose;
        do {
            choose = _getch() - '0' - 1;
        } while (choose < 0 || choose >= HeroNames.size());

        _hero = _heroFactory.createHero(HeroNames[choose]);
        cout << "You choosed: " << HeroNames[choose] << '\n';
    }

    void fight() {        
        int i = rand() % 3;
        _hero->setOpponent(_heroFactory.createHero(HeroNames[i]));
        auto & enemy = _hero->getOpponent();
        enemy.setOpponent(_hero);

        system("cls");

        printSelfState();
        printEnemyState();

        _fighting = true;
        thread menuThread(&GameMode::printFightMenu, this);
        thread opponentThread(&GameMode::controlOpponent, this);

        while (true) {   
            string res;            

            switch (_getch() - '0') {
            case FightMenu::Attack:
                res = _hero->attack();
                break;
            case FightMenu::Ability1:
                res = _hero->Ability_1().cast();
                break;
            case FightMenu::Ability2:
                res = _hero->Ability_2().cast();
                break;
            default:
                break;
            }        

            if (enemy.getCurrentProps().at("Health") <= 0) { 
                _fighting = false;
                menuThread.join();
                opponentThread.join();

                dropItem();
                
                break;
            }
            if (_hero->getCurrentProps().at("Health") <= 0) {
                _fighting = false;
                menuThread.join();
                opponentThread.join();

                cout << "You died! Game over.\n";

                _heroDied = true;
                getchar();
                break;
            }

            printActionResult(res);
            printSelfState();
            printEnemyState();   
        }        
    }

    void controlOpponent() {
        auto & opponent = _hero->getOpponent();
        auto & ability1 = opponent.Ability_1();
        auto & ability2 = opponent.Ability_2();   
        COORD pos = { 50, 13 };

        while (_fighting) {
            string botAction = "";

            if (ability1.getCurCooldown() == 0) {
                ability1.cast();
                botAction = "Opponent casted *" + ability1.getName() + "*";
            }
            else if (ability2.getCurCooldown() == 0) {
                ability2.cast();
                botAction = "Opponent casted *" + ability2.getName() + "*";
            }
            else if (opponent.canAttack()) {
                opponent.attack();
                botAction = "Opponent attacked you.";
            }

            if (botAction.length()) {
                _consoleMutex.lock();

                SetConsoleCursorPosition(_Console, pos);
                cout.width(30);
                cout << left << botAction;

                _consoleMutex.unlock();

                printSelfState();
                printEnemyState();
            }

            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    void dropItem() {
        ostringstream oss;
        oss << "You killed your enemy.\n";

        auto & droppedItem = _items[rand() % _items.size()];
        oss << _hero->getOpponent().getName() << " dropped *" << droppedItem.getName() << "*\n";
        oss << droppedItem.getDescription() << '\n';
        oss << "Effects:\n";
        for (auto it : droppedItem.getEffects()) {
            oss << it.first << ": " << it.second << '\n';
        }

        printActionResult(oss.str());

        if (!_hero->wearItem(droppedItem)) {
            auto equipedItem = _hero->getItem(droppedItem.getSlot());
            cout << "Do you want to change your *" << equipedItem.getName() << "* on *" << droppedItem.getName() << "*?(Y/N)\n";
            char c;

            do {
                c = toupper(_getch());
            } while (c != 'Y' && c != 'N');

            if (c == 'Y') {
                _hero->unwearItem(droppedItem.getSlot());
                _hero->wearItem(droppedItem);
            }
        }
        else {
            getchar();
        }

        _hero->update();        
    }

    void printActionResult(const string & s) {
        COORD pos = { 0, 13 };
        string eraseStr(50, ' ');

        _consoleMutex.lock();

        SetConsoleCursorPosition(_Console, pos);
        cout << eraseStr;
        SetConsoleCursorPosition(_Console, pos);

        cout << s;

        _consoleMutex.unlock();
    }

    void abilitiesInfo() {
        system("cls");
        auto & a1 = _hero->Ability_1(), & a2 = _hero->Ability_2();
        vector<Ability> v{ a1, a2 };
        int i = 1;
        for (auto it : v) {
            cout << "***Ability " << i++ << "***\n";
            cout << "Name: " << it.getName() << '\n';
            cout << "Description: " << it.getDescription() << '\n';
            auto dur = it.getDuration();
            if (dur) cout << "Effect duration: " << dur << " seconds\n";
            cout << "Cooldown: " << it.getCooldown() << " seconds\n";
            cout << "Manacost: " << it.getManacost() << "\n\n";
        }
        cout << "Press any key to go back...";
        _getch();
        system("cls");
    }

    void showInventory() {
        system("cls");
        auto & items = _hero->getEquipedItems();
        
        if (!items.size()) {
            cout << "Inventory is empty.\n";
        }

        for (auto it : items) {
            cout << "Slot: " << it.first << '\n';
            cout << "Name: " << it.second.getName() << '\n';
            cout << "Description: " << it.second.getDescription() << '\n';
            cout << "Effects: \n";
            for (auto it : it.second.getEffects()) {
                cout << it.first << ": " << it.second << '\n';
            }
            cout << "****************************************\n";
        }

        cout << "Press any key to go back...";
        _getch();
    }

    void mainMenu() {              

        while (true) {
            system("cls");  

            if (_heroDied) {
                chooseHero();
                _heroDied = false;
                continue;
            }

            int i = 1;
            cout << "***Main menu***" << '\n';
            for (auto it : _mainmenu) {
                cout << i++ << ". " << it << '\n';
            }

            switch (_getch() - '0') {
            case MainMenu::Fight:
                fight();
                break;

            case MainMenu::Inventory:
                showInventory();
                break;

            case MainMenu::Abilities:
                abilitiesInfo();
                break;

            case MainMenu::ChangeHero:
                chooseHero();
                break;

            case MainMenu::Exit:
                return;

            default:
                break;
            }
        }

    }

    void printFightMenu() {
        COORD pos = { 0, 15 };
        string eraseStr(80, ' ');

        while (_fighting)
        {
            _consoleMutex.lock();

            SetConsoleCursorPosition(_Console, pos);
            cout << eraseStr << '\n' << eraseStr << '\n' << eraseStr << '\n';
            SetConsoleCursorPosition(_Console, pos);


            auto & ability1 = _hero->Ability_1(), &ability2 = _hero->Ability_2();

            cout << "1. Attack\n";
            cout << "2. " + ability1.getName() + ". Manacost: " + to_string(ability1.getManacost()) + ". Cooldown: " + to_string(ability1.getCurCooldown()) << '\n';
            cout << "3. " + ability2.getName() + ". Manacost: " + to_string(ability2.getManacost()) + ". Cooldown: " + to_string(ability2.getCurCooldown()) << '\n';

            _consoleMutex.unlock();

            this_thread::sleep_for(chrono::milliseconds(600));
        }
        SetConsoleCursorPosition(_Console, pos);
        cout << eraseStr << '\n' << eraseStr << '\n' << eraseStr << '\n';
        SetConsoleCursorPosition(_Console, pos);
    }

    void printSelfState() {
        auto props = _hero->getCurrentProps();

        _consoleMutex.lock();        

        SetConsoleCursorPosition(_Console, { 0, 1 });
        string eraseStr(80, ' ');
        for (short i = 0; i < props.size(); i++) {
            cout << eraseStr << '\n';
        }

        SetConsoleCursorPosition(_Console, { 0, 0 });
        cout << "You: " + _hero->getName() << '\n';
        
        for (auto it : props) {
            cout << it.first << ": " << it.second << '\n';
        }
        _consoleMutex.unlock();
    }

    void printEnemyState() {
        COORD pos = { 50, 0 };
        auto & enemy = _hero->getOpponent();

        _consoleMutex.lock();
        SetConsoleCursorPosition(_Console, pos);
        
        cout << "Enemy: " + enemy.getName() << '\n';

        short i = 1;
        auto props = enemy.getCurrentProps();
        for (auto it : props) {
            pos = { 50, i++ };
            SetConsoleCursorPosition(_Console, pos);
            cout << it.first << ": " << it.second << '\n';
        }
        _consoleMutex.unlock();
    }
        
public:
    GameMode();

    void start() {
        chooseHero();

        mainMenu();
    }


    ~GameMode();
};





#endif // !_GAMEMODE