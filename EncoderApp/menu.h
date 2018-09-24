#ifndef MENU_H
#define MENU_H

#include "dictionary.h"

class Menu
{
private:
    Dictionary *dict;
public:
    Menu();
    void printMenu();
    bool getCommand();
};

#endif // MENU_H
