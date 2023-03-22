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
    _game(nullptr),
    _run(false),
    _isInMenu(false),
    _selectedGraph(0),
    _selectedGame(0),
    _testInterface(nullptr),
    _testOnly(false)
{
    if (ac == 1)
        throw std::invalid_argument("Usage: ./arcade displayLib.so [-test] [-test-only] [-h] [--help] [--username=USERNAME]");

    for (int i = 1; i < ac; i++) {
        // Help
        if (std::string(av[i]) == "-h" || std::string(av[i]) == "--help")
            throw std::invalid_argument("Usage: ./arcade displayLib.so [-test] [-test-only] [-h] [--help] [--username=USERNAME]");

        // Test
        else if (std::string(av[i]) == "-test" || std::string(av[i]) == "-test-only") {
            _testInterface = _libLoader.loadGraphicalLib("./tests/test_interface.so");
            _testOnly = std::string(av[i]) == "-test-only";
        }

        // Username
        else if (std::string(av[i]).find("--username=") == 0 and std::string(av[i]).size() > 11)
            _username = std::string(av[i]).substr(11);
    }

    fetchAvailableLibs();
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
    if (_display)
        _libLoader.unloadGraphicalLib(_display);
    if (_game)
        _libLoader.unloadGameLib(_game);
}

std::vector<Arcade::Key> Arcade::Core::fetchPressedKeys()
{
    std::vector<Key> testKeys, pressedKeys;

    // Get normal keys
    if (!_testOnly || _isInMenu)
        pressedKeys = _display->getPressedKeys();

    // Get test keys
    if (_testInterface && !_isInMenu && pressedKeys.empty())
        testKeys = _testInterface->getPressedKeys();

    // Merge keys
    for (auto &key : testKeys)
        if (find(pressedKeys.begin(), pressedKeys.end(), key) == pressedKeys.end())
            pressedKeys.push_back(key);
    return pressedKeys;
}

int Arcade::Core::run(const std::string &libName)
{
    std::vector<Key> oldKeys, pressedKeys, testKeys;

    _run = true;
    _isInMenu = true;
    _selectedGame = 0;
    _selectedGraph = 0;

    // Get the index of the selected graphical
    for (size_t i = 0; i < _graphicalLibs.size(); i++)
        if (libName.find(_graphicalLibs[i]) != std::string::npos)
            _selectedGraph = static_cast<int>(i);

    // Game loop
    while (_run) {
        pressedKeys = fetchPressedKeys();
        if (_isInMenu) {
            _display->renderMenu(_gameLibs, _graphicalLibs, _selectedGame, _selectedGraph, _controls);
        } else {
            _display->render(_game->getGameData());
            _game->handleKeys(pressedKeys);
            _game->update(_username);
        }
        handleEvents(oldKeys, pressedKeys);
        oldKeys = pressedKeys;
    }
    return 0;
}

void Arcade::Core::handleEvents(const std::vector<Key> &oldKeys, const std::vector<Key> &newKeys)
{
    // Load libraries
    if (isKeyPressed(Key::Enter, oldKeys, newKeys) && _isInMenu) {
        if (_testInterface)
            _testInterface = _libLoader.loadGraphicalLib("./tests/test_interface.so");
        return loadSelectedLibrary();
    }
    if (isKeyPressed(Key::Space, oldKeys, newKeys) && _isInMenu) {
        return loadGraphicLibrary("./lib/" + _graphicalLibs[_selectedGraph]);
    }

    // Exit
    if (isKeyPressed(Key::Escape, oldKeys, newKeys)) {
        if (_isInMenu)
            _run = false;
        else
            exitGame();
        return;
    }

    // Change selected game
    if (isKeyPressed(Key::Left, oldKeys, newKeys)
    || isKeyPressed(Key::Right, oldKeys, newKeys)) {
        incrementIndex(_selectedGame, _gameLibs.size(),
                       (isKeyPressed(Key::Left, oldKeys, newKeys) ? -1 : 1));
        if (!_isInMenu)
            loadGameLibrary("./lib/" + _gameLibs[_selectedGame]);
    }

    // Change selected graphical lib
    if (isKeyPressed(Key::Up, oldKeys, newKeys)
    || isKeyPressed(Key::Down, oldKeys, newKeys)) {
        incrementIndex(_selectedGraph, _graphicalLibs.size(),
                       (isKeyPressed(Key::Up, oldKeys, newKeys) ? -1 : 1));
        if (!_isInMenu)
            loadGraphicLibrary("./lib/" + _graphicalLibs[_selectedGraph]);
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
    if (_game) {
        _libLoader.unloadGameLib(_game);
        _game = nullptr;
    }

    IGame *newGame = _libLoader.loadGameLib(name);
    if (!newGame)
        throw LibraryNotLoadedException();
    _game = newGame;
    _isInMenu = false;
}

void Arcade::Core::loadGraphicLibrary(const std::string &name)
{
    if (_display) {
        _libLoader.unloadGraphicalLib(_display);
        _display = nullptr;
    }

    IDisplay *newDisplay = _libLoader.loadGraphicalLib(name);
    if (!newDisplay)
        throw LibraryNotLoadedException();
    _display = newDisplay;
}

void Arcade::Core::fetchAvailableLibs()
{
    LibLoader::LibType libType;
    DirectoryLister dirLister;
    std::string tmpFile;

    _graphicalLibs.clear();
    _gameLibs.clear();

    // Open lib directory
    try {
        dirLister.open("./lib", true);
    } catch (DirectoryLister::OpenFailureException &e) {
        std::cerr << "Error: ./lib: " << e.what() << std::endl;
        exit(84);
    }

    while (true) {
        // No more file in directory
        try {
            tmpFile = dirLister.get();
        } catch (DirectoryLister::NoMoreFileException &e) {
            break;
        }

        // Not a dynamic library
        if (tmpFile.size() < 3 || tmpFile.substr(tmpFile.size() - 3) != ".so")
            continue;

        // Get library type
        libType = _libLoader.getLibType("./lib/" + tmpFile);
        if (libType == LibLoader::GRAPHICAL)
            _graphicalLibs.push_back(tmpFile);
        else if (libType == LibLoader::GAME)
            _gameLibs.push_back(tmpFile);
    }

    // Errors
    if (_graphicalLibs.empty())
        throw NoLibraryException(LibLoader::GRAPHICAL);
    if (_gameLibs.empty())
        throw NoLibraryException(LibLoader::GAME);
}
