#ifndef _HERO
#define _HERO

#include <string>
#include <memory>
#include <thread>
#include <map>
#include "Item.h"

using namespace std;


unsigned constexpr propsCount = 11;


const string PropNames[propsCount] = {
    "Health",
    "MaxHealth",
    "Mana",
    "MaxMana",
    "Armor",
    "Luck",
    "Strength",
    "Intelligence",
    "Agility",
    "Damage",
    "Evasion"
};

class Ability;

class Hero
{
private:
    friend Ability;

    string _name;

    unsigned _attackCooldown = 0;

    shared_ptr<Hero> _opponent;
    
    map<string, Item> _items;
    map<string, float> _itemsEffects;
    map<string, float> _abilitiesEffects;

    const string _mainProp;
    map<string, float> _props;

protected:
    map<string, float> _baseProps;    

protected:
    void recalculateProps() {
        _props["Strength"] = _baseProps["Strength"] + _itemsEffects["Strength"] + _abilitiesEffects["Strength"];
        _props["Agility"] = _baseProps["Agility"] + _itemsEffects["Agility"] + _abilitiesEffects["Agility"];
        _props["Intelligence"] = _baseProps["Intelligence"] + _itemsEffects["Intelligence"] + _abilitiesEffects["Intelligence"];
        _props["Evasion"] = _baseProps["Evasion"] + _itemsEffects["Evasion"] + _abilitiesEffects["Evasion"];
        _props["Luck"] = _baseProps["Luck"] + _itemsEffects["Luck"] + _abilitiesEffects["Luck"];
        _props["Armor"] = _baseProps["Armor"] + _itemsEffects["Armor"] + _abilitiesEffects["Armor"] + _props["Agility"] * 0.6;
        _props["Damage"] = _baseProps["Damage"] + _itemsEffects["Damage"] + _abilitiesEffects["Damage"] + _props[_mainProp];
        _props["MaxHealth"] = _baseProps["MaxHealth"] + _itemsEffects["MaxHealth"] + _abilitiesEffects["MaxHealth"] + _props["Strength"] * 10;
        _props["MaxMana"] = _baseProps["MaxMana"] + _itemsEffects["MaxMana"] + _abilitiesEffects["MaxMana"] + _props["Intelligence"] * 12;
    }

    void calculateProps() {
        recalculateProps();

        _props["Health"] = _props["MaxHealth"];
        _props["Mana"] = _props["MaxMana"];
    }

public:
    Hero(const string & baseProp, const string & name) : _mainProp(baseProp), _name(name) {}

    const string & getName() {
        return _name;
    }

    const map<string, float> & getCurrentProps() {
        return _props;
    }

    bool canAttack() {
        return !_attackCooldown;
    }

    string attack() {
        if (_attackCooldown) {
            return "You can't attack so frequently.";
        }

        double attackDamage;
        string res;

        if (rand() % 101 > _props["Luck"]) {
            attackDamage = _props["Damage"];
        }
        else {
            attackDamage = _props["Damage"] * 2;
            res = "Critical hit. ";
        }

        bool miss = rand() % 101 < _opponent->_props["Evasion"];

        if (!miss) {
            double pureDamage = attackDamage * (100.0 - _opponent->_props["Armor"]) / 100.0;
            _opponent->_props["Health"] -= pureDamage;
            res += "You caused " + to_string(pureDamage) + " damage.";
        }
        else {
            res = "Enemy evades your attack.";
        }

        _attackCooldown = 1500;
        thread attackTimer(&Hero::attackDelay, this);
        attackTimer.detach();

        return res;
    }

    void attackDelay() {
        this_thread::sleep_for(chrono::milliseconds(_attackCooldown));
        _attackCooldown = 0;
    }

    bool wearItem(const Item & item) {

        auto slot = item.getSlot();

        if (_items.find(slot) != _items.end()) {
            return false;
        }

        _items[slot] = item;
        
        for (auto it : item.getEffects()) {
            _itemsEffects[it.first] += it.second;
        }

        recalculateProps();
        return true;
    }

    const map<string, Item> & getEquipedItems() {
        return _items;
    }

    const Item & getItem(const string & slot) {
        return _items[slot];
    }

    void unwearItem(const string & slot) {
        for (auto it : _items[slot].getEffects()) {
            _itemsEffects[it.first] -= it.second;
        }

        _items.erase(slot);
        recalculateProps();
    }
        
    void update() {
        calculateProps();
    }

    void setOpponent(shared_ptr<Hero> opponent) {
        _opponent = opponent;
    }
    Hero & getOpponent() {
        return *_opponent;
    }


    virtual Ability & Ability_1() = 0;
    virtual Ability & Ability_2() = 0;

};


class Ability
{
public:
    enum class Target {
        Self,
        Enemy
    };

private:
    Hero * _owner;
    Target _target;
    string _prop;

    int _effect;
    unsigned
        _effectDuration,
        _manacost,
        _cooldown,
        _curCooldown = 0;

    string
        _name,
        _description;

private:
    void cancellEffect() {
        this_thread::sleep_for(chrono::milliseconds(_effectDuration));

        switch (_target)
        {
        case Ability::Target::Self:
            _owner->_abilitiesEffects[_prop] -= _effect;
            _owner->recalculateProps();
            break;
        case Ability::Target::Enemy:
            _owner->getOpponent()._abilitiesEffects[_prop] -= _effect;
            _owner->getOpponent().recalculateProps();
            break;
        default:
            break;
        }
    }

    void cooldownTimer() {
        while (_curCooldown) {
            this_thread::sleep_for(chrono::seconds(1));
            _curCooldown--;
        }
    }

public:
    Ability(
        Hero * owner,
        const string & name, 
        const string & description, 
        Target target, 
        string prop, 
        int effect, 
        unsigned effectDuration,
        unsigned manacost, 
        unsigned cooldown
    ) : _owner(owner), _name(name), _description(description), _target(target), _prop(prop),
        _effect(effect), _effectDuration(effectDuration), _manacost(manacost), _cooldown(cooldown) {}

    const string & getName() const {
        return _name;
    }

    const string & getDescription() const {
        return _description;
    }

    unsigned getCurCooldown() const {
        return _curCooldown;
    }

    unsigned getCooldown() const {
        return _cooldown;
    }

    unsigned getManacost() const {
        return _manacost;
    }

    double getDuration() const {
        return _effectDuration / 1000;
    }

    string cast() {
        if (_curCooldown != 0) return _name + " on cooldown " + to_string(_curCooldown) + " second left";
        if (_owner->_props["Mana"] < _manacost) return "No enough mana";

        _owner->_props["Mana"] -= _manacost;
        _curCooldown = _cooldown;

        thread cooldownThread(&Ability::cooldownTimer, this);
        cooldownThread.detach();

        switch (_target)
        {
        case Ability::Target::Self:
            _owner->_abilitiesEffects[_prop] += _effect;
            _owner->recalculateProps();
            break;
        case Ability::Target::Enemy:
            _owner->getOpponent()._abilitiesEffects[_prop] += _effect;
            _owner->getOpponent().recalculateProps();
            break;
        default:
            break;
        }

        if (_effectDuration) {
            thread cancellThread(&Ability::cancellEffect, this);
            cancellThread.detach();
        }
        
        return "You casted " + _name;
    }
};



class Knight : public Hero
{
    Ability ability_1 = Ability(
        this,
        "Power hit",
        "Daet po ebalu",
        Ability::Target::Enemy,
        "Health",
        -100, 0, 50, 10
    );
    Ability ability_2 = Ability(
        this,
        "Rage",
        "Increase strength by 40 for 7 seconds", 
        Ability::Target::Self, 
        "Strength", 
        40, 7000, 30, 15
    );


public:
    Knight() : Hero("Strength", "Knight") {
        _baseProps["Strength"] = 35;
        _baseProps["Intelligence"] = 8;
        _baseProps["Agility"] = 24;
        _baseProps["Luck"] = 15;
        _baseProps["Evasion"] = 0;
        _baseProps["MaxHealth"] = 300;
        _baseProps["MaxMana"] = 150;
        _baseProps["Damage"] = 30;
        _baseProps["Armor"] = 9;

        calculateProps();
    }

    virtual Ability & Ability_1() {
        return ability_1;
    }
    virtual Ability & Ability_2() {
        return ability_2;
    }
};

class Archer : public Hero
{
    Ability ability_1 = Ability(
        this,
        "Ghost form",
        "Increase your evasion by 60.",
        Ability::Target::Self,
        "Evasion",
        60, 5000, 60, 10
    );
    Ability ability_2 = Ability(
        this,
        "Power shot",
        "Hit opponent on 150 damage.",
        Ability::Target::Enemy,
        "Health",
        -150, 0, 70, 12
    );


public:
    Archer() : Hero("Agility", "Archer") {
        _baseProps["Strength"] = 20;
        _baseProps["Intelligence"] = 18;
        _baseProps["Agility"] = 32;
        _baseProps["Luck"] = 20;
        _baseProps["Evasion"] = 10;
        _baseProps["MaxHealth"] = 250;
        _baseProps["MaxMana"] = 200;
        _baseProps["Damage"] = 40;
        _baseProps["Armor"] = 4;

        calculateProps();
    }

    virtual Ability & Ability_1() {
        return ability_1;
    }
    virtual Ability & Ability_2() {
        return ability_2;
    }
};

class Wizard : public Hero
{
    Ability ability_1 = Ability(
        this,
        "Magic shot",
        "Magic spell that razrivaet protivniku lico",
        Ability::Target::Enemy,
        "Health",
        -150, 5000, 90, 5
    );
    Ability ability_2 = Ability(
        this,
        "Immunity",
        "Enemy can't hit you for 2.5 seconds",
        Ability::Target::Self,
        "Evasion",
        100, 2500, 60, 15
    );


public:
    Wizard() : Hero("Intelligence", "Wizard") {
        _baseProps["Strength"] = 18;
        _baseProps["Intelligence"] = 31;
        _baseProps["Agility"] = 19;
        _baseProps["Luck"] = 20;
        _baseProps["Evasion"] = 15;
        _baseProps["MaxHealth"] = 250;
        _baseProps["MaxMana"] = 300;
        _baseProps["Damage"] = 25;
        _baseProps["Armor"] = 3;

        calculateProps();
    }

    virtual Ability & Ability_1() {
        return ability_1;
    }
    virtual Ability & Ability_2() {
        return ability_2;
    }
};


#endif // !_HERO