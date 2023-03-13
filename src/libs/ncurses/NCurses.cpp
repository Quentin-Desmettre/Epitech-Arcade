/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** NCurses
*/

#include "../../../include/libs/ncurses/NCurses.hpp"
#include "Menu.hpp"
#include <thread>
#include <chrono>

extern "C" void *createDisplay()
{
    return new Arcade::NCurses::NCurses();
}

extern "C" void deleteDisplay(void *display)
{
    delete reinterpret_cast<Arcade::NCurses::NCurses *>(display);
}

Arcade::NCurses::NCurses::NCurses():
    _win(Window::getStdWin()),
    _fps(60),
    _lastFrame(0)
{
}

Arcade::NCurses::NCurses::~NCurses()
{
    return;
}

void Arcade::NCurses::NCurses::render(const IGameData &gameData)
{
}

void Arcade::NCurses::NCurses::renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics, bool isSelectingGame, int selectedIndex)
{
    waitUntilNextFrame();

    Size winSize = _win.getSize();
    Size menuSize = getMaxSize(getSizeForMenu("Graphical libraries", graphics), getSizeForMenu("Game libraries", games));
    Pos graphicalPos = {
        winSize.first / 2 - menuSize.first - 1,
        (winSize.second - menuSize.second) / 2
    };
    Pos gamePos = {
        winSize.first / 2 + 1,
        graphicalPos.second
    };

    _win.clear();
    if (graphicalPos.first < 0 || gamePos.first + menuSize.first >= winSize.first ||
    graphicalPos.second < 0 || graphicalPos.second + menuSize.second >= winSize.second) {
        _win.drawBox();
        _win.drawText("Window is too small", {(winSize.first - 19) / 2, winSize.second / 2});
        return;
    }

    Menu graphicalLibraries(&_win, "Graphical libraries", graphicalPos, graphics, isSelectingGame ? -1 : selectedIndex, menuSize);
    Menu gameLibraries(&_win, "Game libraries", gamePos, games, isSelectingGame ? selectedIndex: - 1, menuSize);

    graphicalLibraries.render();
    gameLibraries.render();
}

std::vector<Arcade::Key> Arcade::NCurses::NCurses::getPressedKeys()
{
    int ch;
    std::vector<Key> keys;

    while ((ch = getch()) != ERR) {
        switch (ch) {
            case 'z':
                keys.push_back(Key::Up);
                break;
            case 's':
                keys.push_back(Key::Down);
                break;
            case 'q':
                keys.push_back(Key::Left);
                break;
            case 'd':
                keys.push_back(Key::Right);
                break;
            case 10:
                keys.push_back(Key::Enter);
                break;
            case 27:
                keys.push_back(Key::Escape);
                break;
        }
    }
    return keys;
}

Size Arcade::NCurses::NCurses::getSizeForMenu(const std::string &title, const std::vector<std::string> &items)
{
    // Menu should be large enough to contain the biggest item + 8 characters, for padding and box.
    // Or, name.size + 6 characters, for padding and box.
    int requiredWidth = 0;
    for (const auto &item : items) {
        if (item.size() > requiredWidth)
            requiredWidth = static_cast<int>(item.size());
    }
    if (title.size() > requiredWidth)
        requiredWidth = static_cast<int>(title.size() + 6);
    else
        requiredWidth += 8;
    return {requiredWidth, static_cast<int>(items.size() + 5)};
}

Size Arcade::NCurses::NCurses::getMaxSize(const Size &a, const Size &b)
{
    Size max;

    max.first = std::max(a.first, b.first);
    max.second = std::max(a.second, b.second);
    return max;
}

void Arcade::NCurses::NCurses::setFramerateLimit(int fps)
{
    _fps = fps;
}

void Arcade::NCurses::NCurses::waitUntilNextFrame()
{
    if (_fps == -1)
        return;
    long now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();
    if (now - _lastFrame < 1000 / _fps)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / _fps - (now - _lastFrame)));

    _lastFrame = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();
}
