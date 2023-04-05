/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** test
*/

#pragma once

#include <memory>
#include <fstream>
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
        void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                        int selectedGame, int selectedDisplay,
                        const ControlMap &controls, const std::string &username, const std::string &bestScoreUsername, int bestScore) override;
    private:
        void getNextEvent();
        class Event {
            public:
                Arcade::Key key;
                long timeLeft;
        };
        long _clock;
        Event _event;
        std::ifstream _file;
    };
