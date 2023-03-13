/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Window
*/

#include "Window.hpp"
#include <stdexcept>

Arcade::NCurses::Window::Window()
{
    _win = initscr();
    _pos = {0, 0};
    timeout(0);
    noecho();
    getSize();
    curs_set(0);
}

Arcade::NCurses::Window::Window(Window *parent, const std::pair<int, int> &pos,
                                const std::pair<int, int> &size)
{
    if (!parent)
        throw std::runtime_error("Parent window is null");
    parent->_children.push_back(this);
    _pos = pos;
    _size = size;
    _win = subwin(parent->_win, size.second, size.first, pos.second, pos.first);
}

Arcade::NCurses::Window &Arcade::NCurses::Window::getStdWin()
{
    static Window win;
    return win;
}

Arcade::NCurses::Window::~Window()
{
    if (_win == stdscr)
        endwin();
    else
        delwin(_win);
}

Pos Arcade::NCurses::Window::getPos() const
{
    return _pos;
}

Size Arcade::NCurses::Window::getSize()
{
    int x, y;

    getmaxyx(_win, y, x);
    _size = {x, y};
    return _size;
}

void Arcade::NCurses::Window::drawBox()
{
    box(_win, 0, 0);
}

void Arcade::NCurses::Window::drawText(const std::string &text, const Pos &pos)
{
    mvwprintw(_win, pos.second, pos.first, "%s", text.c_str());
}

void Arcade::NCurses::Window::clear()
{
    auto size = getSize();
    std::string cleaner(size.first * size.second, ' ');

    wmove(_win, 0, 0);
    wprintw(_win, "%s", cleaner.c_str());
}
