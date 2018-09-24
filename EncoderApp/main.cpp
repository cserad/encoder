#include <iostream>
#include <string>

#include "menu.h"

int main()
{
    Menu *menu = new Menu();
    bool run = true;
    while (run) {
        menu->printMenu();
        menu->getCommand();
    }
    return 0;
}
