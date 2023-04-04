/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** test
*/

#include <regex>
#include <cstdio>
#include <chrono>
#include "test.hpp"

extern "C"
{
    void *createDisplay() {
        return new Arcade::TestInterface();
    }

    void deleteDisplay(void *display) {
        delete reinterpret_cast<Arcade::TestInterface *>(display);
    }
}

Arcade::TestInterface::TestInterface()
{
    _clock = std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count();
    _file = std::ifstream("src/libs/test/keys.txt");
    getNextEvent();
}

Arcade::TestInterface::~TestInterface()
{
}

void Arcade::TestInterface::getNextEvent()
{
    std::string buffer;
    std::smatch match;
    std::regex expression("^([A-Z]+)\\(([0-9]+(?:\\.[0-9]+)?)\\)$");

    _event.key = Unknown;
    _event.timeLeft = 0;
    getline(_file, buffer);
    if (std::regex_match(buffer, match, expression)) {
        if (match[1].str() == "ESCAPE")
            _event.key = Escape;
        else if (match[1].str() == "Z")
            _event.key = Z;
        else if (match[1].str() == "Q")
            _event.key = Q;
        else if (match[1].str() == "S")
            _event.key = S;
        else if (match[1].str() == "D")
            _event.key = D;
        else if (match[1].str() == "SPACE")
            _event.key = Space;
        else if (match[1].str() == "UP")
            _event.key = Up;
        else if (match[1].str() == "DOWN")
            _event.key = Down;
        else if (match[1].str() == "RIGHT")
            _event.key = Right;
        else if (match[1].str() == "LEFT")
            _event.key = Left;
        else if (match[1].str() == "ENTER")
            _event.key = Enter;
        _event.timeLeft = std::stof(match[2].str()) * 1000;
    }
}

std::vector<Arcade::Key> Arcade::TestInterface::getPressedKeys()
{
    std::vector<Arcade::Key> keys;
    float dif = (std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count() - _clock);
    _clock = std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count();

    _event.timeLeft -= dif;
    if (_event.timeLeft <= 0)
        getNextEvent();
    if (_event.timeLeft > 0 && _event.key != Unknown)
        keys.push_back(_event.key);
    return keys;
}

void Arcade::TestInterface::render(__attribute_maybe_unused__ Arcade::IGameData &gameData)
{
}

void Arcade::TestInterface::renderMenu(UNUSED const std::vector<std::string> &games,
                                       UNUSED const std::vector<std::string> &graphics,
                                       UNUSED int selectedGame,
                                       UNUSED int selectedDisplay,
                                       UNUSED const ControlMap &controls,
                                       UNUSED const std::string &username,
                                       UNUSED const std::string &bestScoreUsername,
                                       UNUSED int bestScore)
{
}
