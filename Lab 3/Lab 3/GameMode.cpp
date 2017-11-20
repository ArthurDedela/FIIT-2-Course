#include "GameMode.h"



GameMode::GameMode()
{
    _items.push_back(Item(
        "Head",
        "Dragon Skin helmet",
        "This helmet made from the skin of the first dragon - Alduin.",
        2,
        pair<string, float>("MaxHealth", 150),
        pair<string, float>("Armor", 8)
    ));
    _items.push_back(Item(
        "Body",
        "Steel Armor",
        "Provides basic body protection",
        1,
        pair<string, float>("Armor", 7)
    ));
    _items.push_back(Item(
        "ArmRight",
        "Steel Sword",
        "Usual steel sword",
        1,
        pair<string, float>("Damage", 15)
    ));
    _items.push_back(Item(
        "ArmLeft",
        "Elven Blade",
        "Fksd flfe alwe jfewk qlks fwje",
        2,
        pair<string, float>("Damage", 18),
        pair<string, float>("Agility", 8)
    ));
    _items.push_back(Item(
        "Boots",
        "Leather boots",
        "Common boots, that give you some armor",
        1,
        pair<string, float>("Armor", 3)
    ));
    _items.push_back(Item(
        "Cloak",
        "Invisibility cloak",
        "When you wear this cloak, your enemies should try hard to hit you.",
        1,
        pair<string, float>("Evasion", 40)
    ));
    _items.push_back(Item(
        "Amulet",
        "Amulet of Fortune",
        "They say, it brings good luck",
        1,
        pair<string, float>("Luck", 20)
    ));
    _items.push_back(Item(
        "ArmRight",
        "Elven sword",
        "Ffd qlkwd ajske wjqdjxj",
        3,
        pair<string, float>("Luck", 5),
        pair<string, float>("Damage", 30),
        pair<string, float>("Agility", 13)
    ));
    _items.push_back(Item(
        "Body",
        "Dragon armor",
        "Armor made from dragon bones",
        3,
        pair<string, float>("Strength", 12),
        pair<string, float>("Armor", 10),
        pair<string, float>("Evasion", 8)
    ));
    _items.push_back(Item(
        "Head",
        "Lether Helm",
        "Common helmet",
        1,
        pair<string, float>("Armor", 4)
    ));
}


GameMode::~GameMode()
{
}
