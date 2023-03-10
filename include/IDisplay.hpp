/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_
#include "IGame.hpp"

namespace Arcade {
    class IDisplay;
};

class Arcade::IDisplay {
    public:
        virtual ~IDisplay() = 0;
        virtual std::vector<Key> getPressedKeys() = 0;
        virtual void render(const IGameData &gameData) = 0;
        virtual void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics, int selectedGame, int selectedGraphic) = 0;
};

#endif /* !IDISPLAY_HPP_ */