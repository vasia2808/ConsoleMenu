#include <conio.h>
#include <map>
#include <sstream>
#include <Windows.h>
#include "Console.h"

using namespace std;

void Console::setCursorVisible(bool visible)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = visible;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Console::clear()
{
    system("cls");
}

void Console::SetEncoding()
{
    system("chcp 1251");
}

Key Console::readKey()
{
    map<char, Key> keys;

    keys.emplace(13, Key::Enter);
    keys.emplace(27, Key::Esc);
    keys.emplace(72, Key::Up);
    keys.emplace(80, Key::Down);

    keys.emplace('a', Key::A);
    keys.emplace('b', Key::B);
    keys.emplace('c', Key::C);
    keys.emplace('e', Key::E);
    keys.emplace('g', Key::G);
    keys.emplace('n', Key::N);
    keys.emplace('o', Key::O);
    keys.emplace('r', Key::R);
    keys.emplace('s', Key::S);

    keys.emplace('A', Key::A);
    keys.emplace('B', Key::B);
    keys.emplace('C', Key::C);
    keys.emplace('E', Key::E);
    keys.emplace('G', Key::G);
    keys.emplace('N', Key::N);
    keys.emplace('O', Key::O);
    keys.emplace('R', Key::R);
    keys.emplace('S', Key::S);

    keys.emplace('ô', Key::A);
    keys.emplace('è', Key::B);
    keys.emplace('ñ', Key::C);
    keys.emplace('ó', Key::E);
    keys.emplace('ï', Key::G);
    keys.emplace('ò', Key::N);
    keys.emplace('ù', Key::O);
    keys.emplace('ê', Key::R);
    keys.emplace('³', Key::S);

    keys.emplace('Ô', Key::A);
    keys.emplace('È', Key::B);
    keys.emplace('Ñ', Key::C);
    keys.emplace('Ó', Key::E);
    keys.emplace('Ï', Key::G);
    keys.emplace('Ò', Key::N);
    keys.emplace('Ù', Key::O);
    keys.emplace('Ê', Key::R);
    keys.emplace('²', Key::S);

    char ikey = _getch();

    return keys[(_kbhit() ? _getch() : ikey)];
}

int Console::getHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(-12), &consoleInfo);
    return consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
}

int Console::getWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(-12), &consoleInfo);
    return consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
}

void Console::hideCursor()
{
    setCursorVisible(false);
}

void Console::setCursorPosition(int x, int y)
{
    COORD cursorLoc;

    cursorLoc.X = x;
    cursorLoc.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorLoc);
}

void Console::setSize(int cols, int rows)
{
    stringstream command;
    command << "mode con cols=" << cols << " lines=" << rows;
    system(command.str().c_str());
}

void Console::setTitle(string title)
{
    string tempStr = "title " + title;
    system(tempStr.c_str());
}

void Console::showCursor()
{
    setCursorVisible(true);
}