/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include "GameInterfaces.hpp"

namespace Arcade {
    class IDisplay;
};

class Arcade::IDisplay {
    public:
        virtual ~IDisplay() = default;
        virtual std::vector<Key> getPressedKeys() = 0;
        virtual void render(IGameData &gameData) = 0;
        virtual void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                                int selectedGame, int selectedDisplay,
                                const ControlMap &controls) = 0;
};

#endif /* !IDISPLAY_HPP_ */
