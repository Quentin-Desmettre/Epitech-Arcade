/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Core
*/

#include "Core.hpp"
#include <iostream>
#include <algorithm>
#include <filesystem>
#include "GameUtils.hpp"

Arcade::Core::Core::LibraryNotLoadedException::LibraryNotLoadedException()
{
    _message = "Error: " + LibLoader::getInstance().getLastError();
}

const char *Arcade::Core::Core::LibraryNotLoadedException::what() const noexcept
{
    return _message.c_str();
}

Arcade::Core::Core::NoLibraryException::NoLibraryException(LibLoader::LibType type)
{
    if (type == LibLoader::GRAPHICAL)
        _message = "Error: No graphical library could be loaded.";
    else if (type == LibLoader::GAME)
        _message = "Error: No game library could be loaded.";
}

const char *Arcade::Core::Core::NoLibraryException::what() const noexcept
{
    return _message.c_str();
}

Arcade::Core::Core::Core(int ac, char **av):
    _libLoader(LibLoader::getInstance()),
    _display(nullptr),
    _game(nullptr),
    _run(false),
    _isInMenu(false),
    _selectedGraph(0),
    _selectedGame(0),
    _testInterface(nullptr),
    _testOnly(false),
    _username(""),
    _bestScoreUser(""),
    _bestScore(0)
{
    if (ac == 1)
        throw std::invalid_argument("Usage: ./arcade displayLib.so [-test]");

    // Test
    if (ac > 2 && (std::string(av[2]) == "-test" || std::string(av[2]) == "-test-only")) {
        _testInterface = _libLoader.loadGraphicalLib("./tests/test_interface.so");
        _testOnly = std::string(av[2]) == "-test-only";
    } else if (ac > 2)
        throw std::invalid_argument("Usage: ./arcade displayLib.so [-test]");

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

Arcade::Core::Core::~Core()
{
    if (_display)
        _libLoader.unloadGraphicalLib(_display);
    if (_game)
        _libLoader.unloadGameLib(_game);
}

std::vector<Arcade::Key> Arcade::Core::Core::fetchPressedKeys()
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

int Arcade::Core::Core::run(const std::string &libName)
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
    updateBestScore();
    while (_run) {
        pressedKeys = fetchPressedKeys();
        if (_isInMenu) {
            _display->renderMenu(_gameLibs, _graphicalLibs, _selectedGame,
                                 _selectedGraph, _controls, _username,
                                 _bestScoreUser, _bestScore);
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

void Arcade::Core::Core::handleEvents(const std::vector<Key> &oldKeys, const std::vector<Key> &newKeys)
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
    if (isKeyPressed(Key::F4, oldKeys, newKeys)) {
        if (!_isInMenu)
            exitGame();
        _run = false;
        return;
    }

    // Change selected game
    if (isKeyPressed(Key::Left, oldKeys, newKeys)
    || isKeyPressed(Key::Right, oldKeys, newKeys)) {
        incrementIndex(_selectedGame, _gameLibs.size(),
                       (isKeyPressed(Key::Left, oldKeys, newKeys) ? -1 : 1));
        if (!_isInMenu)
            loadGameLibrary("./lib/" + _gameLibs[_selectedGame]);
        else
            updateBestScore();
    }

    // Change selected graphical lib
    if (isKeyPressed(Key::Up, oldKeys, newKeys)
    || isKeyPressed(Key::Down, oldKeys, newKeys)) {
        incrementIndex(_selectedGraph, _graphicalLibs.size(),
                       (isKeyPressed(Key::Up, oldKeys, newKeys) ? -1 : 1));
        if (!_isInMenu)
            loadGraphicLibrary("./lib/" + _graphicalLibs[_selectedGraph]);
    }

    // Change username
    if (_isInMenu)
        changeUsername(oldKeys, newKeys);
}

void Arcade::Core::Core::incrementIndex(int &index, std::size_t len, int dir)
{
    index += dir;
    if (index >= static_cast<int>(len))
        index = 0;
    else if (index < 0)
        index = static_cast<int>(len) - 1;
}

void Arcade::Core::Core::exitGame()
{
    _isInMenu = true;
    _libLoader.unloadGameLib(_game);
    _game = nullptr;
}

bool Arcade::Core::Core::isKeyPressed(Key key, const std::vector<Key> &pressedKeys) const
{
    return std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end();
}

bool Arcade::Core::Core::isKeyPressed(Key key, const std::vector<Key> &oldKeys, const std::vector<Key> &newKeys) const
{
    return !isKeyPressed(key, oldKeys) && isKeyPressed(key, newKeys);
}

void Arcade::Core::Core::loadSelectedLibrary()
{
    loadGraphicLibrary("./lib/" + _graphicalLibs[_selectedGraph]);
    loadGameLibrary("./lib/" + _gameLibs[_selectedGame]);
}

void Arcade::Core::Core::loadGameLibrary(const std::string &name)
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

void Arcade::Core::Core::loadGraphicLibrary(const std::string &name)
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

void Arcade::Core::Core::fetchAvailableLibs()
{
    LibLoader::LibType libType;
    const std::filesystem::path sandbox{"lib"};

    _graphicalLibs.clear();
    _gameLibs.clear();

    // Get libs
    for (auto &file: std::filesystem::directory_iterator{sandbox}) {
        if (file.path().extension() != ".so")
            continue;
        libType = _libLoader.getLibType(file.path().string());
        if (libType == LibLoader::GRAPHICAL)
            _graphicalLibs.push_back(file.path().filename().string());
        else if (libType == LibLoader::GAME)
            _gameLibs.push_back(file.path().filename().string());
    }

    // Errors
    if (_graphicalLibs.empty())
        throw NoLibraryException(LibLoader::GRAPHICAL);
    if (_gameLibs.empty())
        throw NoLibraryException(LibLoader::GAME);
}

void Arcade::Core::Core::changeUsername(const std::vector<Key> &oldKeys,
                                        const std::vector<Key> &newKeys)
{
    static const std::map<Key, char> keyToChar = {
            {Key::A, 'a'}, {Key::B, 'b'}, {Key::C, 'c'}, {Key::D, 'd'},
            {Key::E, 'e'}, {Key::F, 'f'}, {Key::G, 'g'}, {Key::H, 'h'}, {Key::I, 'i'},
            {Key::J, 'j'}, {Key::K, 'k'}, {Key::L, 'l'}, {Key::M, 'm'}, {Key::N, 'n'},
            {Key::O, 'o'}, {Key::P, 'p'}, {Key::Q, 'q'}, {Key::R, 'r'}, {Key::S, 's'},
            {Key::T, 't'}, {Key::U, 'u'}, {Key::V, 'v'}, {Key::W, 'w'}, {Key::X, 'x'},
            {Key::Y, 'y'}, {Key::Z, 'z'}, {Key::Num0, '0'}, {Key::Num1, '1'},
            {Key::Num2, '2'}, {Key::Num3, '3'}, {Key::Num4, '4'}, {Key::Num5, '5'},
            {Key::Num6, '6'}, {Key::Num7, '7'}, {Key::Num8, '8'}, {Key::Num9, '9'},
    };

    std::vector<Key> newlyPressedKeys;
    std::set_difference(newKeys.begin(), newKeys.end(),
                        oldKeys.begin(), oldKeys.end(),
                        std::back_inserter(newlyPressedKeys));

    for (auto &key: newlyPressedKeys) {
        if (key == Key::Backspace && !_username.empty() &&
        std::find(newKeys.begin(), newKeys.end(), Key::LControl) != newKeys.end())
            _username.clear();
        else if (key == Key::Backspace && !_username.empty())
            _username.pop_back();
        else if (keyToChar.find(key) != keyToChar.end())
            _username += keyToChar.at(key);
    }
}

void Arcade::Core::Core::updateBestScore()
{
    // Reset scores
    _bestScore = 0;
    _bestScoreUser = "N/A";

    // Load game lib
    IGame *game = _libLoader.loadGameLib("./lib/" + _gameLibs[_selectedGame]);
    if (!game)
        return;

    // Get best score
    Arcade::Games::GameUtils::fetchBestScores(game->getGameData().getGameName(), _bestScoreUser, _bestScore);

    // Unload
    _libLoader.unloadGameLib(game);
}
