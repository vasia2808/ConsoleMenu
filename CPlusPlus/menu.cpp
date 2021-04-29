#include <iomanip>
#include "menu.h"

Menu::Menu()
{
    SET_HOTKEY(Key::Up, &Menu::arrowMoveUp);
    SET_HOTKEY(Key::Down, &Menu::arrowMoveDown);
    SET_HOTKEY(Key::Enter, &Menu::select);
}

void Menu::clearItems()
{
    items.clear();
}

int Menu::show()
{
    refresh();

    Key key;

    do
    {
        key = Console::readKey();

        if (!(items.empty() && (key == Key::Enter || key == Key::Up || key == Key::Down)))
        {
            int result = hotkeys[key](Key::Null);

            if (result)
            {
                return result;
            }

            refresh();
        }
    }
    while (key != Key::Esc);

    onExited();
    return 0;
}

void Menu::refresh()
{
    Console::clear();
    Console::hideCursor();
    
    drawHeader();
    drawItems();
    drawArrow();
}

void Menu::removeItemAt(int index)
{
    if (index == items.size() - 1)
    {
        setArrowPosition(index - 1);
    }

    items.erase(items.begin() + index);
}

void Menu::onExited()
{
    Console::clear();
    Console::showCursor();
}

void Menu::drawHeader()
{
    cout << setw(arrow.length()) << "" << headerText << endl;
    drawLine(1);
}

void Menu::drawLine(int position)
{
    Console::setCursorPosition(0, position);

    for (int i = 0; i < Console::getWidth(); i++)
    {
        cout << '-';
    }

    cout << endl;
}

void Menu::drawItems()
{
    for (int i = 0; i < (int)items.size(); i++)
    {
        Console::setCursorPosition(arrow.length(), ITEMS_LIST_POSITION + i);
        cout << items[i].name << endl;
    }
}

int Menu::arrowMoveUp(Key key)
{
    setArrowPosition(arrowPosition - 1);
    return 0;
}

int Menu::arrowMoveDown(Key key)
{
    setArrowPosition(arrowPosition + 1);
    return 0;
}

int Menu::select(Key key)
{
    return items[arrowPosition].select(&items[arrowPosition]);
}

void Menu::setArrowPosition(int position)
{
    if (!items.empty())
    {
        position = ((int)items.size() + position) % (int)items.size();
        clearArrow();
        arrowPosition = position;
        drawArrow();
    }
}

void Menu::clearArrow()
{
    Console::setCursorPosition(0, arrowPosition + ITEMS_LIST_POSITION);
    cout << setw(arrow.length()) << "";
}

void Menu::drawArrow()
{
    if (!items.empty())
    {
        Console::setCursorPosition(0, arrowPosition + ITEMS_LIST_POSITION);
        cout << arrow;
    }
}

void Menu::setSize(int width, int height)
{
    Console::setSize(width, height);
}

string Menu::getHeaderText()
{
    return headerText;
}

void Menu::setHeaderText(string text)
{
    headerText = text;
}

int Menu::getArrowPosition()
{
    return arrowPosition;
}