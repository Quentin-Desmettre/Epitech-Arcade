/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_
#include "IDisplay.hpp"
#include <ncurses.h>
#include <vector>
#include "Window.hpp"
#include <memory>
#include "Menu.hpp"

/**
 * @brief A wrapper around the ncurses library.
 */
namespace Arcade::Graphics::NCurses {
    class NCurses;
}

typedef std::vector<std::string> StringVector;

/**
 * @brief The NCurses graphical library.
 */
class Arcade::Graphics::NCurses::NCurses: public Arcade::IDisplay {
public:
    /**
     * @brief Creates a new NCurses graphical library.
     */
    NCurses();
    ~NCurses() override;

    /**
     * @see Arcade::IDisplay::getPressedKeys()
     */
    std::vector<Key> getPressedKeys() override;

    /**
     * @see Arcade::IDisplay::render()
     */
    void render(IGameData &gameData) override;

    /**
     * @see Arcade::IDisplay::renderMenu()
     */
    void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                    int selectedGame, int selectedDisplay,
                    const ControlMap &controls, const std::string &username, const std::string &bestScoreUsername, int bestScore) override;

    /**
     * @brief Sets the framerate limit.
     * @param fps The framerate limit.
     */
    void setFramerateLimit(int fps);

protected:
private:
    static Size getSizeForMenu(const std::string &title, const std::vector<std::string> &items);
    static Size getSizeForMenu(const std::string &title, const ControlMap &items);
    static std::vector<std::string> getNames(const ControlMap &items);
    static Size getMaxSize(const Size &a, const Size &b, const Size &c);
    static bool isPositionOk(const Pos &pos, const Size &size, const Size &winSize);
    void createMenus(bool isSelectingGame, int selectedIndex);
    void renderScores(IGameData &gameData);
    void renderEntities(IGameData &gameData);
    void renderControls(const ControlMap &controls);

    void waitUntilNextFrame();

    using UniqueMenu = std::unique_ptr<Arcade::Graphics::NCurses::Menu>;

    Window _win;
    UniqueMenu _graphicalMenu, _gameMenu, _controlMenu;

    // Cache data
    StringVector _graphicalNames, _gameNames;
    ControlMap _controls;

    Size _lastWinSize;
    int _fps;
    long _lastFrame;
    int _baseInputDelay;
};

/**
 * @brief Creates a new NCurses graphical library.
 * See Arcade::IDisplay::createDisplay() for more information.
 */
extern "C" void *createDisplay();

/**
 * @brief Deletes a NCurses graphical library.
 * See Arcade::IDisplay::deleteDisplay() for more information.
 */
extern "C" void deleteDisplay(void *display);

#endif /* !NCURSES_HPP_ */
