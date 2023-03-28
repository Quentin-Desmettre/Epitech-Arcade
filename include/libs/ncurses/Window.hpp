/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Window
*/

#ifndef EPITECH_ARCADE_WINDOW_HPP
#define EPITECH_ARCADE_WINDOW_HPP
#include <utility>
#include <ncurses.h>
#include <vector>
#include <string>
#include "GameInterfaces.hpp"
#include "libs/ncurses/Texture.hpp"

namespace Arcade::Graphics::NCurses {
    class Window;
} // Arcade

typedef std::pair<int, int> Pos;
typedef std::pair<int, int> Size;

class Arcade::Graphics::NCurses::Window {
public:
    Window();
    Window(Window *parent, const Pos &pos, const Size &size);
    static Window &getStdWin();
    ~Window();

    Pos getPos() const;
    Size getSize();

    void drawBox();
    void draw(const std::string &text, const Pos &pos);
    void draw(const Texture &texture, Pos pos);
    void clear();

    static Arcade::Key getKey();

private:

    std::pair<int, int> _pos;
    std::pair<int, int> _size;
    std::vector<Window *> _children;
    WINDOW *_win;

    static const std::map<int, Arcade::Key> _keyMap;
    static bool _isInit, _hasColors;
};

#endif //EPITECH_ARCADE_WINDOW_HPP
