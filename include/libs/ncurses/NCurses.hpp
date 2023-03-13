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

class Arcade::NCurses::NCurses: public Arcade::IDisplay {
public:
    NCurses();
    ~NCurses() override;

    std::vector<Key> getPressedKeys() override;
    void render(const IGameData &gameData) override;
    void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics, bool isSelectingGame, int selectedIndex) override;
    void setFramerateLimit(int fps);

protected:
private:
    static Size getSizeForMenu(const std::string &title, const std::vector<std::string> &items);
    static Size getMaxSize(const Size &a, const Size &b);
    void createMenus(const std::vector<std::string> &games, const std::vector<std::string> &graphics, bool isSelectingGame, int selectedIndex, const Size &winSize);

    void waitUntilNextFrame();

    using UniqueMenu = std::unique_ptr<Arcade::NCurses::Menu>;

    Window &_win;
    UniqueMenu _graphicalMenu, _gameMenu;
    Size _lastWinSize;
    int _fps;
    long _lastFrame;
};

#endif /* !NCURSES_HPP_ */
