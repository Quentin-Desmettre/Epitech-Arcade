/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Core
*/

#include "Core.hpp"
#include "DirectoryLister.hpp"
#include <iostream>
#include <algorithm>

Arcade::Core::LibraryNotLoadedException::LibraryNotLoadedException()
{
    _message = "Error: " + LibLoader::getInstance().getLastError();
}

const char *Arcade::Core::LibraryNotLoadedException::what() const noexcept
{
    return _message.c_str();
}

Arcade::Core::NoLibraryException::NoLibraryException(LibLoader::LibType type)
{
    if (type == LibLoader::GRAPHICAL)
        _message = "Error: No graphical library could be loaded.";
    else if (type == LibLoader::GAME)
        _message = "Error: No game library could be loaded.";
}

const char *Arcade::Core::NoLibraryException::what() const noexcept
{
    return _message.c_str();
}

Arcade::Core::Core(int ac, char **av):
    _libLoader(LibLoader::getInstance()),
    _display(nullptr),
    _game(nullptr)
{
    LibLoader::LibType libType;
    DirectoryLister dirLister;
    std::string tmpFile;

    if (ac != 2)
        throw std::invalid_argument("Usage: ./arcade displayLib.so");

    try {
        dirLister.open("./lib", true);
    } catch (DirectoryLister::OpenFailureException &e) {
        std::cerr << "Error: ./lib: " << e.what() << std::endl;
        exit(84);
    }

    while (1) {
        try {
            tmpFile = dirLister.get();
        } catch (DirectoryLister::NoMoreFileException &e) {
            break;
        }

        if (tmpFile.size() < 3 || tmpFile.substr(tmpFile.size() - 3) != ".so")
            continue;
        libType = _libLoader.getLibType("./lib/" + tmpFile);
        if (libType == LibLoader::GRAPHICAL)
            _graphicalLibs.push_back(tmpFile);
        else if (libType == LibLoader::GAME)
            _gameLibs.push_back(tmpFile);
    }

    if (_graphicalLibs.empty())
        throw NoLibraryException(LibLoader::GRAPHICAL);
    if (_gameLibs.empty())
        throw NoLibraryException(LibLoader::GAME);
    loadGraphicLibrary(av[1]);
    _controls = {
            {"Quit", "ESC"},
            {"Load game & graph", "ENTER"},
            {"Load graph", "SPACE"},
            {"Select game", "LEFT/RIGHT"},
            {"Select graph", "UP/DOWN"},
    };
}

Arcade::Core::~Core()
{
    _libLoader.unloadGraphicalLib(_display);
    _libLoader.unloadGameLib(_game);
}

int Arcade::Core::run()
{
    std::vector<Key> oldKeys, pressedKeys;

    _run = true;
    _isInMenu = true;
    _selectedGame = 0;
    _selectedGraph = 0;
    while (_run) {
        pressedKeys = _display->getPressedKeys();
        if (!_isInMenu && _game->exit())
            exitGame();
        if (_isInMenu) {
            _display->renderMenu(_gameLibs, _graphicalLibs, _selectedGame, _selectedGraph, _controls);
            handleMenuEvents(oldKeys, pressedKeys);
        } else {
            _display->render(_game->getGameData());
            _game->handleKeys(pressedKeys);
            _game->update();
        }
        oldKeys = pressedKeys;
    }
    return 0;
}

void Arcade::Core::handleMenuEvents(const std::vector<Key> &oldKeys, const std::vector<Key> &newKeys)
{
    if (isKeyPressed(Key::Enter, oldKeys, newKeys))
        return loadSelectedLibrary();
    if (isKeyPressed(Key::Space, oldKeys, newKeys))
        return loadGraphicLibrary("./lib/" + _graphicalLibs[_selectedGraph]);
    if (isKeyPressed(Key::Escape, oldKeys, newKeys)) {
        _run = false;
        return;
    }

    // Change selected game
    if (isKeyPressed(Key::Left, oldKeys, newKeys)
    || isKeyPressed(Key::Right, oldKeys, newKeys)) {
        incrementIndex(_selectedGame, _gameLibs.size(),
                       (isKeyPressed(Key::Left, oldKeys, newKeys) ? -1 : 1));
    }

    // Change selected graphical lib
    if (isKeyPressed(Key::Up, oldKeys, newKeys)
    || isKeyPressed(Key::Down, oldKeys, newKeys)) {
        incrementIndex(_selectedGraph, _graphicalLibs.size(),
                       (isKeyPressed(Key::Up, oldKeys, newKeys) ? -1 : 1));
    }
}

void Arcade::Core::incrementIndex(int &index, std::size_t len, int dir)
{
    index += dir;
    if (index >= static_cast<int>(len))
        index = 0;
    else if (index < 0)
        index = static_cast<int>(len) - 1;
}

void Arcade::Core::exitGame()
{
    _isInMenu = true;
    _libLoader.unloadGameLib(_game);
    _game = nullptr;
}

bool Arcade::Core::isKeyPressed(Key key, const std::vector<Key> &pressedKeys) const
{
    return std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end();
}

bool Arcade::Core::isKeyPressed(Key key, const std::vector<Key> &oldKeys, const std::vector<Key> &newKeys) const
{
    return !isKeyPressed(key, oldKeys) && isKeyPressed(key, newKeys);
}

void Arcade::Core::loadSelectedLibrary()
{
    loadGraphicLibrary("./lib/" + _graphicalLibs[_selectedGraph]);
    loadGameLibrary("./lib/" + _gameLibs[_selectedGame]);
}

void Arcade::Core::loadGameLibrary(const std::string &name)
{
    if (_game)
        _libLoader.unloadGameLib(_game);

    IGame *newGame = _libLoader.loadGameLib(name);
    if (!newGame)
        throw LibraryNotLoadedException();
    _game = newGame;
    _isInMenu = false;
}

void Arcade::Core::loadGraphicLibrary(const std::string &name)
{
    if (_display)
        _libLoader.unloadGraphicalLib(_display);

    IDisplay *newDisplay = _libLoader.loadGraphicalLib(name);
    if (!newDisplay)
        throw LibraryNotLoadedException();
    _display = newDisplay;
}
