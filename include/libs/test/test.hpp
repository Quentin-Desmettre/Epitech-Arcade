/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** test
*/

#pragma once

#include <memory>
#include "IDisplay.hpp"

namespace Arcade {
    class TestInterface;
};

class Arcade::TestInterface : public Arcade::IDisplay {
    public:
        TestInterface();
        ~TestInterface();
        std::vector<Key> getPressedKeys() override;
        void render(IGameData &gameData) override;
        void renderMenu(const std::vector<std::string> &games,
        const std::vector<std::string> &graphics, int selectedGame, int selectedGraph, const ControlMap &map) override;
    private:
    };
