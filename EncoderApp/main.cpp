#include "menu.h"

int main()
{
    Menu menu;
    menu.loadDict();

    bool run = true;

    while (run) {
        menu.printMenu();
        run = menu.getCommand();
    }

    return 0;
}
