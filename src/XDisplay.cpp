/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** XDisplay
*/

#include "XDisplay.hpp"
#include <iostream>
#include <fstream>

void Arcade::XDisplay::setInputDelay(int ms)
{
    std::string command = "gsettings set org.gnome.desktop.peripherals.keyboard delay " + std::to_string(ms);

    system(command.c_str());
}

int Arcade::XDisplay::getInputDelay()
{
    system("gsettings get org.gnome.desktop.peripherals.keyboard delay | tail -c +8 > /tmp/delay");
    std::ifstream f("/tmp/delay");
    int delay;

    if (!f)
        return 0;
    f >> delay;
    return delay;
}
