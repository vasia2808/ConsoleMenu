#pragma once
#include <functional>
#include "menu.h"

class MainMenu : public Menu
{
private:
    int wrapper(function<int()> func);
    int printHelloWorld(MenuItem* sender);
    int printThisItemName(MenuItem* sender);

public:
    MainMenu();
};

