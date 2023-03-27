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

class Arcade::XDisplay {
public:
    static void setInputDelay(int ms);
    static int getInputDelay();
};


#endif //EPITECH_ARCADE_XDISPLAY_HPP
