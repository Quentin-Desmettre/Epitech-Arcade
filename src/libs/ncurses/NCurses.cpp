/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** NCurses
*/

#include "NCurses.hpp"
#include "Menu.hpp"
#include <thread>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <vector>
#include "XDisplay.hpp"

extern "C" void *createDisplay()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    if (has_colors() && can_change_color())
        start_color();
    return new Arcade::Graphics::NCurses::NCurses();
}

extern "C" void deleteDisplay(void *display)
{
    delete reinterpret_cast<Arcade::Graphics::NCurses::NCurses *>(display);
    endwin();
}

Arcade::Graphics::NCurses::NCurses::NCurses():
    _win(),
    _lastWinSize({0, 0}),
    _fps(60),
    _lastFrame(0)
{
//    _baseInputDelay = Arcade::XDisplay::getInputDelay();
//    Arcade::XDisplay::setInputDelay(0);
}

void Arcade::Graphics::NCurses::NCurses::render(IGameData &gameData)
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
    auto size = _win.getSize();
    _win.clear();
    renderScores(gameData);
    renderEntities(gameData);
    renderControls(gameData.getControls());
    if (gameData.isGameOver()) {
        Texture t("", size.first / 4, size.second / 8);
        t.setBackgroundColor(Color::RED);
        t.setTextColor(Color::WHITE);
        t.setContent(' ');
        _win.draw(t, {size.first / 2 - size.first / 8, size.second / 2 - size.second / 16 - 1});
        _win.draw("GAME OVER", {size.first / 2 - 4, size.second / 2 - 1});
    }
    refresh();
}

void Arcade::Graphics::NCurses::NCurses::renderControls(const ControlMap &controls)
{
    Size winSize = _win.getSize();
    Window controlsWin(&_win, {0, 3}, {winSize.first * 0.25, winSize.second - 5});

    controlsWin.drawBox();
    controlsWin.draw("Controls:", {1, 1});
    int i = 2;
    for (const auto &control: controls) {
        controlsWin.draw(control.first + ":", {1, i});
        controlsWin.draw(control.second, {10, i});
        i++;
    }
}

void Arcade::Graphics::NCurses::NCurses::renderScores(IGameData &gameData)
{
    Size winSize = _win.getSize();
    Window scores(&_win, {winSize.first * 0.15, 0}, {winSize.first * 0.7, 3});

    scores.drawBox();
    int totalLen = 0;
    for (const auto &score: gameData.getScores())
        totalLen += static_cast<int>(score.first.size() + 2 + std::to_string(score.second).size() + 3);
    int xOffset = (winSize.first * 0.7 - totalLen) / 2;
    for (const auto &score: gameData.getScores()) {
        scores.draw(score.first + ": " + std::to_string(score.second) + " | ", {xOffset, 1});
        xOffset += static_cast<int>(score.first.size() + 2 + std::to_string(score.second).size() + 3);
    }
}

void Arcade::Graphics::NCurses::NCurses::renderEntities(IGameData &gameData)
{
    Size winSize = _win.getSize();
    Size availableSize = {winSize.first, winSize.second - 3};
    int cellSize = std::min(availableSize.first / gameData.getMapSize().first, availableSize.second / gameData.getMapSize().second);
    Size gameSize = {cellSize * gameData.getMapSize().first * 2, cellSize * gameData.getMapSize().second + 1};
    Window game(&_win, {winSize.first / 2 - gameSize.first / 2, 3}, gameSize);

    gameData.getEntities();
    static std::map<std::string, std::unique_ptr<Texture>> textures;
    for (const auto &entity: gameData.getEntities()) {
        Size entitySize = {
                (cellSize * entity->getSize().first) * 2,
                (cellSize * entity->getSize().second)
        };
        std::string path = "assets/" + gameData.getGameName() + "/ncurses/" + entity->getTexture();
        if (textures.find(path) == textures.end())
            textures[path] = std::make_unique<Texture>(path, entitySize.first, entitySize.second);
        else
            textures[path]->setSize(entitySize.first, entitySize.second);
        std::vector<std::pair<float, float>> entityPos = entity->getPosition();
        for (auto &pos: entityPos) {
            pos.first *= cellSize * 2;
            pos.second *= cellSize;
            pos.second += 1;
            game.draw(*textures[path].get(), pos);
        }
    }
    textures.clear();
}

void Arcade::Graphics::NCurses::NCurses::renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                                                    int selectedGame, int selectedGraph,
                                                    const ControlMap &map, const std::string &username, const std::string &bestScoreUsername, int bestScore)
{
    waitUntilNextFrame();

    // Re-create menus if files/winSize differ
    Size winSize = _win.getSize();
    if (winSize != _lastWinSize || games != _gameNames || graphics != _graphicalNames || map != _controls) {
        _lastWinSize = winSize;
        _gameNames = games;
        _graphicalNames = graphics;
        _controls = map;
        createMenus(selectedGame, selectedGraph);
    }

    // Check if pointers are valid
    _win.clear();
    if (!_graphicalMenu || !_gameMenu) {
        _win.drawBox();
        _win.draw("Window is too small", {(winSize.first - 19) / 2, winSize.second / 2});
        refresh();
        return;
    }

    // Username & best score
    _win.draw("Username: " + username, {1, 1});
    _win.draw("Best score: " + bestScoreUsername + " : " + std::to_string(bestScore), {1, 2});

    // If selected has changed, update it
    _gameMenu->setSelected(selectedGame);
    _graphicalMenu->setSelected(selectedGraph);

    // Render menus
    _gameMenu->render();
    _graphicalMenu->render();
    _controlMenu->render();

    refresh();
}

void Arcade::Graphics::NCurses::NCurses::createMenus(bool isSelectingGame, int selectedIndex)
{
    Size winSize = _win.getSize();
    Size menuSize = getMaxSize(getSizeForMenu("Graphical libraries", _graphicalNames), getSizeForMenu("Game libraries", _gameNames),
                               getSizeForMenu("Controls", _controls));
    Pos controlsPos = {
            winSize.first / 2 - menuSize.first * 1.5 + 1,
            (winSize.second - menuSize.second) / 2
    };
    Pos graphicalPos = {
            winSize.first / 2 - menuSize.first / 2 + 1,
            (winSize.second - menuSize.second) / 2
    };
    Pos gamePos = {
            winSize.first / 2 + menuSize.first / 2 + 1,
            graphicalPos.second
    };

    if (!isPositionOk(controlsPos, menuSize, winSize)
    || !isPositionOk(graphicalPos, menuSize, winSize)
    || !isPositionOk(gamePos, menuSize, winSize)) {
        _gameMenu = nullptr;
        _graphicalMenu = nullptr;
        _controlMenu = nullptr;
        return;
    }
    _gameMenu = std::make_unique<Menu>(&_win, "Game libraries", gamePos, _gameNames, isSelectingGame ? selectedIndex: - 1, menuSize);
    _graphicalMenu = std::make_unique<Menu>(&_win, "Graphical libraries", graphicalPos, _graphicalNames, isSelectingGame ? -1 : selectedIndex, menuSize);
    _controlMenu = std::make_unique<Menu>(&_win, "Controls", controlsPos, getNames(_controls), -1, menuSize);
}

Size Arcade::Graphics::NCurses::NCurses::getSizeForMenu(const std::string &title, const std::vector<std::string> &items)
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

Size Arcade::Graphics::NCurses::NCurses::getSizeForMenu(const std::string &title, const ControlMap &items)
{
    return getSizeForMenu(title, getNames(items));
}

std::vector<std::string> Arcade::Graphics::NCurses::NCurses::getNames(const ControlMap &items)
{
    std::vector<std::string> stringItems{items.size(), ""};

    std::transform(items.begin(), items.end(), stringItems.begin(), [](const auto &item) {
        return item.first + ": " + item.second;
    });
    return stringItems;
}

Size Arcade::Graphics::NCurses::NCurses::getMaxSize(const Size &a, const Size &b, const Size &c)
{
    Size max;

    max.first = std::max(a.first, std::max(b.first, c.first));
    max.second = std::max(a.second, std::max(b.second, c.second));
    return max;
}

void Arcade::Graphics::NCurses::NCurses::setFramerateLimit(int fps)
{
    _fps = fps;
}

void Arcade::Graphics::NCurses::NCurses::waitUntilNextFrame()
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

bool Arcade::Graphics::NCurses::NCurses::isPositionOk(const Pos &pos, const Size &size, const Size &winSize)
{
    return pos.first >= 0 && pos.first + size.first < winSize.first &&
           pos.second >= 0 && pos.second + size.second < winSize.second;
}

std::vector<Arcade::Key> Arcade::Graphics::NCurses::NCurses::getPressedKeys()
{
    std::vector<Key> keys;
    Key k;

    while ((k = Arcade::Graphics::NCurses::Window::getKey()) != Key::Unknown)
        keys.push_back(k);
    return keys;
}

Arcade::Graphics::NCurses::NCurses::~NCurses() noexcept
{
//    Arcade::XDisplay::setInputDelay(_baseInputDelay);
}
