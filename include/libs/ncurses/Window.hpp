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

namespace Arcade {
    namespace NCurses {
        class Window;
    }
} // Arcade

typedef std::pair<int, int> Pos;
typedef std::pair<int, int> Size;

class Arcade::NCurses::Window {
public:
    Window(Window *parent, const Pos &pos, const Size &size);
    static Window &getStdWin();
    ~Window();

    Pos getPos() const;
    Size getSize();

    void drawBox();
    void drawText(const std::string &text, const Pos &pos);
    void clear();
private:
    Window();

    std::pair<int, int> _pos;
    std::pair<int, int> _size;
    std::vector<Window *> _children;
    WINDOW *_win;
};

#endif //EPITECH_ARCADE_WINDOW_HPP
