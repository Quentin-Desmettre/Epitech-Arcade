/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Window
*/

#include "Window.hpp"
#include <stdexcept>

const std::map<int, Arcade::Key> Arcade::NCurses::Window::_keyMap = {
        {ERR, Arcade::Key::Unknown},
        {KEY_UP, Arcade::Key::Up},
        {KEY_DOWN, Arcade::Key::Down},
        {KEY_LEFT, Arcade::Key::Left},
        {KEY_RIGHT, Arcade::Key::Right},
        {10, Arcade::Key::Enter},
        {'A', Arcade::Key::A},
        {'B', Arcade::Key::B},
        {'C', Arcade::Key::C},
        {'D', Arcade::Key::D},
        {'E', Arcade::Key::E},
        {'F', Arcade::Key::F},
        {'G', Arcade::Key::G},
        {'H', Arcade::Key::H},
        {'I', Arcade::Key::I},
        {'J', Arcade::Key::J},
        {'K', Arcade::Key::K},
        {'L', Arcade::Key::L},
        {'M', Arcade::Key::M},
        {'N', Arcade::Key::N},
        {'O', Arcade::Key::O},
        {'P', Arcade::Key::P},
        {'Q', Arcade::Key::Q},
        {'R', Arcade::Key::R},
        {'S', Arcade::Key::S},
        {'T', Arcade::Key::T},
        {'U', Arcade::Key::U},
        {'V', Arcade::Key::V},
        {'W', Arcade::Key::W},
        {'X', Arcade::Key::X},
        {'Y', Arcade::Key::Y},
        {'Z', Arcade::Key::Z},
        {'a', Arcade::Key::A},
        {'b', Arcade::Key::B},
        {'c', Arcade::Key::C},
        {'d', Arcade::Key::D},
        {'e', Arcade::Key::E},
        {'f', Arcade::Key::F},
        {'g', Arcade::Key::G},
        {'h', Arcade::Key::H},
        {'i', Arcade::Key::I},
        {'j', Arcade::Key::J},
        {'k', Arcade::Key::K},
        {'l', Arcade::Key::L},
        {'m', Arcade::Key::M},
        {'n', Arcade::Key::N},
        {'o', Arcade::Key::O},
        {'p', Arcade::Key::P},
        {'q', Arcade::Key::Q},
        {'r', Arcade::Key::R},
        {'s', Arcade::Key::S},
        {'t', Arcade::Key::T},
        {'u', Arcade::Key::U},
        {'v', Arcade::Key::V},
        {'w', Arcade::Key::W},
        {'x', Arcade::Key::X},
        {'y', Arcade::Key::Y},
        {'z', Arcade::Key::Z},
        {'0', Arcade::Key::Num0},
        {'1', Arcade::Key::Num1},
        {'2', Arcade::Key::Num2},
        {'3', Arcade::Key::Num3},
        {'4', Arcade::Key::Num4},
        {'5', Arcade::Key::Num5},
        {'6', Arcade::Key::Num6},
        {'7', Arcade::Key::Num7},
        {'8', Arcade::Key::Num8},
        {'9', Arcade::Key::Num9},
        {27, Arcade::Key::Escape},
        {KEY_F(1), Arcade::Key::F1},
        {KEY_F(2), Arcade::Key::F2},
        {KEY_F(3), Arcade::Key::F3},
        {KEY_F(4), Arcade::Key::F4},
        {KEY_F(5), Arcade::Key::F5},
        {KEY_F(6), Arcade::Key::F6},
        {KEY_F(7), Arcade::Key::F7},
        {KEY_F(8), Arcade::Key::F8},
        {KEY_F(9), Arcade::Key::F9},
        {KEY_F(10), Arcade::Key::F10},
        {KEY_F(11), Arcade::Key::F11},
        {KEY_F(12), Arcade::Key::F12},
        {KEY_F(13), Arcade::Key::F13},
        {KEY_F(14), Arcade::Key::F14},
        {KEY_F(15), Arcade::Key::F15}
};

bool Arcade::NCurses::Window::_isInit = false;
bool Arcade::NCurses::Window::_hasColors = false;

Arcade::NCurses::Window::Window()
{
    _win = initscr();
    _pos = {0, 0};
    timeout(0);
    noecho();
    getSize();
    curs_set(0);
    keypad(stdscr, TRUE);
    _isInit = true;

    if (has_colors() && can_change_color()) {
        _hasColors = true;
        start_color();
    } else
        _hasColors = false;
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

void Arcade::NCurses::Window::draw(const std::string &text, const Pos &pos)
{
    mvwprintw(_win, pos.second, pos.first, "%s", text.c_str());
}

void Arcade::NCurses::Window::draw(const Texture &text, const Pos &pos)
{
    auto colorPair = COLOR_PAIR(text.getColorPair());

    if (_hasColors)
        wattron(_win, colorPair);
    mvwprintw(_win, pos.second, pos.first, "%s", text.getContent().c_str());
    if (_hasColors)
        wattroff(_win, colorPair);
}

void Arcade::NCurses::Window::clear()
{
    auto size = getSize();
    std::string cleaner(size.first * size.second, ' ');

    wmove(_win, 0, 0);
    wprintw(_win, "%s", cleaner.c_str());
}

Arcade::Key Arcade::NCurses::Window::getKey()
{
    if (!_isInit)
        throw std::runtime_error("Window is not initialized");
    int ch = getch();
    if (_keyMap.find(ch) == _keyMap.end())
        return Arcade::Key::Unknown;
    return _keyMap.at(ch);
}
