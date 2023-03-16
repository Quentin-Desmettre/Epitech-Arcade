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
#include <cmath>

#define foreach(item, container) for (auto &item: container)

extern "C" void *createDisplay()
{
    return new Arcade::NCurses::NCurses();
}

extern "C" void deleteDisplay(void *display)
{
    delete reinterpret_cast<Arcade::NCurses::NCurses *>(display);
}

Arcade::NCurses::NCurses::NCurses():
    _win(),
    _lastWinSize({0, 0}),
    _fps(60),
    _lastFrame(0)
{
}

void Arcade::NCurses::NCurses::render(IGameData &gameData)
{
    waitUntilNextFrame();

    /*
     * Display scores at the top
     * Display controls on the left
     * put the game in the center, filling as much space as possible.
     *
     * The game is n by m cell, and the displayed game is x by y chars.
     * So, each game cell measure x/n by y/m chars.
     *
     * Each texture is composed of a unique char, and an optional color.
     *
     * When displaying the texture, if it takes 1 cell, we display it as x/n by y/m chars.
     * If it takes t x-cells, we display it as t*x/n by y/m chars.
     * If it takes t y-cells, we display it as x/n by t*y/m chars.
     */
    Size winSize = _win.getSize();
    Window scores(&_win, {winSize.first * 0.15, 0}, {winSize.first * 0.7, 3});
//    Window controls(&_win, {0, 3}, {0, 0});

    Size availableSize = {winSize.first, winSize.second - 3};
    int cellSize = std::min(availableSize.first / gameData.getMapSize().first, availableSize.second / gameData.getMapSize().second);
    Size gameSize = {cellSize * gameData.getMapSize().first, cellSize * gameData.getMapSize().second};
    Window game(&_win, {winSize.first / 2- gameSize.first, 3}, gameSize);

    // Display scores
    scores.drawBox();
    int xOffset = 1;
    for (const auto &score: gameData.getScores()) {
        scores.draw(score.first + ": " + std::to_string(score.second) + " | ", {xOffset, 1});
        xOffset += static_cast<int>(score.first.size() + 2 + std::to_string(score.second).size() + 3);
    }

    // Display controls
//    controls.drawBox();
//    controls.draw("Controls", {1, 1});

    // Display game
    gameData.getEntities();
    foreach (entity, gameData.getEntities()) {
        Size entitySize = {
                std::round(cellSize * entity->getSize().first),
                std::round(cellSize * entity->getSize().second)
        };
        Pos entityPos = {
                std::round(cellSize * entity->getPosition().first - entitySize.first / 2),
                std::round(cellSize * entity->getPosition().second - entitySize.second / 2)
        };
        Texture tex(entity->getTexture(), entitySize.first, entitySize.second);
        game.draw(tex, entityPos);
    }
}

void Arcade::NCurses::NCurses::renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics, bool isSelectingGame, int selectedIndex)
{
    waitUntilNextFrame();

    // Re-create menus if files/winSize differ
    Size winSize = _win.getSize();
    if (winSize != _lastWinSize) {
        _lastWinSize = winSize;
        createMenus(games, graphics, isSelectingGame, selectedIndex, winSize);
    }

    // Check if pointers are valid
    _win.clear();
    if (!_graphicalMenu || !_gameMenu) {
        _win.drawBox();
        _win.draw("Window is too small", {(winSize.first - 19) / 2, winSize.second / 2});
        return;
    }

    // If selected has changed, update it
    if (isSelectingGame) {
        _gameMenu->setSelected(selectedIndex);
        _graphicalMenu->setSelected(-1);
    } else {
        _graphicalMenu->setSelected(selectedIndex);
        _gameMenu->setSelected(-1);
    }

    // Render menus
    _gameMenu->render();
    _graphicalMenu->render();
}

void Arcade::NCurses::NCurses::createMenus(const std::vector<std::string> &games, const std::vector<std::string> &graphics, bool isSelectingGame, int selectedIndex, const Size &winSize)
{
    Size menuSize = getMaxSize(getSizeForMenu("Graphical libraries", graphics), getSizeForMenu("Game libraries", games));
    Pos graphicalPos = {
            winSize.first / 2 - menuSize.first - 1,
            (winSize.second - menuSize.second) / 2
    };
    Pos gamePos = {
            winSize.first / 2 + 1,
            graphicalPos.second
    };

    if (graphicalPos.first < 0 || gamePos.first + menuSize.first >= winSize.first ||
        graphicalPos.second < 0 || graphicalPos.second + menuSize.second >= winSize.second) {
        _gameMenu = nullptr;
        _graphicalMenu = nullptr;
        return;
    }
    _gameMenu = std::make_unique<Menu>(&_win, "Game libraries", gamePos, games, isSelectingGame ? selectedIndex: - 1, menuSize);
    _graphicalMenu = std::make_unique<Menu>(&_win, "Graphical libraries", graphicalPos, graphics, isSelectingGame ? -1 : selectedIndex, menuSize);
}

std::vector<Arcade::Key> Arcade::NCurses::NCurses::getPressedKeys()
{
    Key k;
    std::vector<Key> keys;

    while ((k = Arcade::NCurses::Window::getKey()) != Key::Unknown)
        keys.push_back(k);
    return keys;
}

Size Arcade::NCurses::NCurses::getSizeForMenu(const std::string &title, const std::vector<std::string> &items)
{
    // Menu should be large enough to contain the biggest item + 8 characters, for padding and box.
    // Or, name.size + 6 characters, for padding and box.
    std::size_t requiredWidth = 0;
    for (const auto &item : items) {
        if (item.size() > requiredWidth)
            requiredWidth = item.size();
    }
    if (title.size() > requiredWidth)
        requiredWidth = title.size() + 6;
    else
        requiredWidth += 8;
    return {static_cast<int>(requiredWidth), static_cast<int>(items.size() + 5)};
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
