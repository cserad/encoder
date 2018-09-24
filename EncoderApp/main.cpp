#include <iostream>
#include <string>

#include "menu.h"

int main()
{
    Menu *menu = new Menu();
    bool run = true;
    while (run) {
        menu->printMenu();
        run = menu->getCommand();
    }
    return 0;
}
