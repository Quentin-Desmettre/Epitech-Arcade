/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** ADisplay
*/

#include "ADisplay.hpp"
#include "XDisplay.hpp"

std::vector<Arcade::Key> Arcade::ADisplay::getPressedKeys()
{
    // Check all value from enum
    std::vector<Key> pressedKeys;
    Key k;

    for (int i = A; i < KeyCount; i++) {
        k = static_cast<Key>(i);
        if (XDisplay::isKeyPressed(k))
            pressedKeys.push_back(k);
    }
    return pressedKeys;
}
