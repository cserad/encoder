#pragma once

#include "dictionary.h"

class Menu
{
public:
    Menu();
    void printMenu();
    bool getCommand();
    void loadDict();

private:
    Dictionary dict;
};
