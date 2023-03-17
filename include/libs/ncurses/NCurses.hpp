/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_
#include "../../IDisplay.hpp"
#include <ncurses.h>
#include <vector>
#include "Window.hpp"
#include <memory>
#include "Menu.hpp"

namespace Arcade {
    namespace NCurses {
        class NCurses;
    }
}

typedef std::vector<std::string> StringVector;

class Arcade::NCurses::NCurses: public Arcade::IDisplay {
public:
    NCurses();
    ~NCurses() override = default;

    std::vector<Key> getPressedKeys() override;
    void render(IGameData &gameData) override;
    void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                    int selectedGame, int selectedGraph, const ControlMap &map) override;
    void setFramerateLimit(int fps);

protected:
private:
    static Size getSizeForMenu(const std::string &title, const std::vector<std::string> &items);
    static Size getSizeForMenu(const std::string &title, const ControlMap &items);
    static std::vector<std::string> getNames(const ControlMap &items);
    static Size getMaxSize(const Size &a, const Size &b, const Size &c);
    static bool isPositionOk(const Pos &pos, const Size &size, const Size &winSize);
    void createMenus(bool isSelectingGame, int selectedIndex);

    void waitUntilNextFrame();

    using UniqueMenu = std::unique_ptr<Arcade::NCurses::Menu>;

    Window _win;
    UniqueMenu _graphicalMenu, _gameMenu, _controlMenu;

    // Cache data
    StringVector _graphicalNames, _gameNames;
    ControlMap _controls;

    Size _lastWinSize;
    int _fps;
    long _lastFrame;
};

#endif /* !NCURSES_HPP_ */
