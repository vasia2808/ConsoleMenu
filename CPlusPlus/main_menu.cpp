#include <iomanip>
#include <sstream>
#include "main_menu.h"

MainMenu::MainMenu()
{
    setSize(74, 24);
    setHeaderText("Main Menu");

    ADD_ITEM("Print \"Hello World\"", &MainMenu::printHelloWorld);
    ADD_ITEM("Print this item name", &MainMenu::printThisItemName);
}

int MainMenu::wrapper(function<int()> func)
{
    Console::clear();
    Console::showCursor();

    int result = func();

    if (!result)
    {
        cout << endl;
        cout << "Press any key to continue!" << endl;
        Console::readKey();
    }

    return result;
}

int MainMenu::printHelloWorld(MenuItem* sender)
{
    return wrapper([]()
        {
            cout << "Hello World" << endl;
            return 0;
        });
}

int MainMenu::printThisItemName(MenuItem* sender)
{
    return wrapper([]()
        {
            cout << "Print this item name" << endl;
            return 0;
        });
}