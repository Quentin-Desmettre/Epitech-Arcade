/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** ADisplay
*/

#ifndef EPITECH_ARCADE_ADISPLAY_HPP
#define EPITECH_ARCADE_ADISPLAY_HPP

#include "IDisplay.hpp"

namespace Arcade {
    class ADisplay;
};

class Arcade::ADisplay: public Arcade::IDisplay {
    public:
        ADisplay() = default;
        ~ADisplay() override = default;

        std::vector<Key> getPressedKeys() override;
};

#endif //EPITECH_ARCADE_ADISPLAY_HPP
