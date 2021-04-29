#pragma once
#include <map>
#include <vector>
#include "console.h"
#include "event_handler.h"

#define ADD_ITEM(name, method) addItem(name, this, method);
#define SET_ITEM(name, method, index) setItem(name, this, method, index);
#define SET_HOTKEY(key, method) setHotkey(key, this, method);

using namespace std;

class Menu
{
public:
    class MenuItem
    {
    public:
        string name;
        TEvent<MenuItem*> select;

        template<class T>
        MenuItem(string name, T* menu, int (T::* method)(MenuItem*)) : name(name)
        {
            select += createEventHandler(menu, method);
        }
    };

    Menu();

    void setSize(int width, int height);
    string getHeaderText();
    void setHeaderText(string text);
    int getArrowPosition();
    void setArrowPosition(int position);

    template<class T>
    void addItem(string name, T* menu, int (T::* method)(MenuItem*))
    {
        items.push_back(MenuItem(name, menu, method));
    }

    template<class T>
    void setItem(string name, T* menu, int (T::* method)(MenuItem*), int index)
    {
        items[index] = MenuItem(name, menu, method);
    }

    template<class T>
    void setHotkey(Key key, T* menu, int (T::* method)(Key))
    {
        if (hotkeys.find(key) == hotkeys.end())
        {
            TEvent<Key> event;
            event += createEventHandler(menu, method);
            hotkeys.emplace(key, event);
        }
        else
        {
            hotkeys[key] += createEventHandler(menu, method);
        }
    }

    void removeItemAt(int index);
    void clearItems();
    void refresh();
    int show();

private:
    const int ITEMS_LIST_POSITION = 2;
    const string arrow = " => ";

    int arrowPosition = 0;
    string headerText;

    vector<MenuItem> items;
    map<Key, TEvent<Key>> hotkeys;

    void onExited();
    void drawHeader();
    void drawLine(int position);
    void drawItems();
    int arrowMoveUp(Key key);
    int arrowMoveDown(Key key);
    int select(Key key);
    void clearArrow();
    void drawArrow();
};