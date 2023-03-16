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
    _isSelectingGame = false;
    _selectedIndex = 0;
    while (_run) {
        pressedKeys = _display->getPressedKeys();
        // if (!_isInMenu && _game->exit())
        //     exitGame();
        if (_isInMenu) {
            _display->renderMenu(_gameLibs, _graphicalLibs, _isSelectingGame, _selectedIndex);
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
    std::size_t len;
    int dir;

    if (isKeyPressed(Key::Enter, oldKeys, newKeys))
        return loadSelectedLibrary();
    if (isKeyPressed(Key::Escape, oldKeys, newKeys)) {
        _run = false;
        return;
    }
    if (isKeyPressed(Key::Left, oldKeys, newKeys)
    || isKeyPressed(Key::Right, oldKeys, newKeys)) {
        _isSelectingGame = !_isSelectingGame;
        len = (_isSelectingGame ? _gameLibs.size() : _graphicalLibs.size());
        _selectedIndex = (_selectedIndex >= len ? len - 1 : _selectedIndex);
    }
    if (isKeyPressed(Key::Up, oldKeys, newKeys)
    || isKeyPressed(Key::Down, oldKeys, newKeys)) {
        dir = (isKeyPressed(Key::Up, oldKeys, newKeys) ? -1 : 1);
        len = (_isSelectingGame ? _gameLibs.size() : _graphicalLibs.size());
        _selectedIndex += dir;
        if (_selectedIndex >= len)
            _selectedIndex = (dir > 0 ? 0 : len - 1);
    }
}

void Arcade::Core::exitGame()
{
    std::size_t len;

    _isInMenu = true;
    _libLoader.unloadGameLib(_game);
    _game = nullptr;
    len = (_isSelectingGame ? _gameLibs.size() : _graphicalLibs.size());
    _selectedIndex = (_selectedIndex >= len ? len - 1 : _selectedIndex);
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
    if (_isSelectingGame)
        loadGameLibrary("./lib/" + _gameLibs[_selectedIndex]);
    else
        loadGraphicLibrary("./lib/" + _graphicalLibs[_selectedIndex]);
}

void Arcade::Core::loadGameLibrary(const std::string &name)
{
    IGame *newGame = _libLoader.loadGameLib(name);

    if (!newGame)
        throw LibraryNotLoadedException();
    if (_game)
        _libLoader.unloadGameLib(_game);
    _game = newGame;
    _isInMenu = false;
}

void Arcade::Core::loadGraphicLibrary(const std::string &name)
{
    IDisplay *newDisplay = _libLoader.loadGraphicalLib(name);

    if (!newDisplay)
        throw LibraryNotLoadedException();
    if (_display)
        _libLoader.unloadGraphicalLib(_display);
    _display = newDisplay;
}
