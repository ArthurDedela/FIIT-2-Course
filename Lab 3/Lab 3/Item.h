#ifndef _ITEM
#define _ITEM
#include <string>
#include <map>
#include <cstdarg>

using namespace std;
using itemEffect = pair<string, float>;

unsigned constexpr slotsCount = 7;

const string slots[slotsCount] = {
    "Head",
    "Body",
    "ArmLeft",
    "ArmRight",
    "Boots",
    "Cloak",
    "Amulet"
};

class Item
{
private:
    map<string, float> _propEffects;

    string _slot, _name, _description;


public:
    Item() = default;

    Item(
        const string & slot,
        const string & name,
        const string & description,
        unsigned effectsCount,
        const itemEffect effect,
        ...
    ) : _slot(slot), _name(name), _description(description) {
        va_list p;
        va_start(p, effectsCount);

        while (effectsCount--) {
            _propEffects.insert(va_arg(p, itemEffect));
        }

        va_end(p);
    }

    const string & getSlot() const {
        return _slot;
    }

    const string & getName() const {
        return _name;
    }

    const string & getDescription() {
        return _description;
    }

    const map<string, float> & getEffects() const {
        return _propEffects;
    }


    ~Item();
};


#endif