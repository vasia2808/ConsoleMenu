#pragma once
#include <iostream>

enum Key
{
    Null,
    Enter,
    Esc,
    Up,
    Down,
    A,
    B,
    C,
    E,
    G,
    N,
    O,
    R,
    S,
};

class Console
{
private:
    static void setCursorVisible(bool visible);

public:

    static void clear();
    static void SetEncoding();
    static Key readKey();
    static int getHeight();
    static int getWidth();
    static void hideCursor();
    static void setCursorPosition(int x, int y);
    static void setSize(int cols, int rows);
    static void setTitle(std::string title);
    static void showCursor();
};