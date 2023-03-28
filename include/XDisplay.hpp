/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** XDisplay
*/

#ifndef EPITECH_ARCADE_XDISPLAY_HPP
#define EPITECH_ARCADE_XDISPLAY_HPP

namespace Arcade {
    class XDisplay;
};

/**
 * @brief A wrapper around the X11 display.
 */
class Arcade::XDisplay {
public:
    /**
     * @brief Set the input delay.
     * @param ms The delay in milliseconds.
     */
    static void setInputDelay(int ms);

    /**
     * @brief Get the input delay.
     * @return The input delay in milliseconds.
     */
    static int getInputDelay();
};

#endif //EPITECH_ARCADE_XDISPLAY_HPP
