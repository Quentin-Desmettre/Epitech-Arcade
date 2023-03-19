/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** test
*/

#include <cstdio>
#include <iostream>
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
}

Arcade::TestInterface::~TestInterface()
{
}

std::vector<Arcade::Key> Arcade::TestInterface::getPressedKeys()
{
    std::vector<Arcade::Key> keys;

    keys.push_back(Arcade::Key::Z);
    keys.push_back(Arcade::Key::Q);
    return keys;
}

void Arcade::TestInterface::render(__attribute_maybe_unused__ Arcade::IGameData &gameData)
{
}

void Arcade::TestInterface::renderMenu(__attribute_maybe_unused__ const std::vector<std::string> &games,
__attribute_maybe_unused__ const std::vector<std::string> &graphics, __attribute_maybe_unused__ int selectedGame,
__attribute_maybe_unused__ int selectedGraph, __attribute_maybe_unused__ const Arcade::ControlMap &map)
{
}
