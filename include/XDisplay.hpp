/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** XDisplay
*/

#ifndef EPITECH_ARCADE_XDISPLAY_HPP
#define EPITECH_ARCADE_XDISPLAY_HPP
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "GameInterfaces.hpp"

#define CONSTRUCTOR __attribute__((constructor))
#define DESTRUCTOR __attribute__((destructor))

namespace Arcade {
    class XDisplay;
};

class Arcade::XDisplay {
public:
    static Display *getDisplay() CONSTRUCTOR;
    static void closeDisplay() DESTRUCTOR;
    static void getKeyboardState(char state[32]);
    static bool isKeyPressed(Arcade::Key code);
    static void setInputDelay(int ms);
    static int getInputDelay();

private:
    static KeySym keyToKeySym(Arcade::Key key);
    static KeyCode keyToKeyCode(Arcade::Key key);
    static Display *display;
};


#endif //EPITECH_ARCADE_XDISPLAY_HPP
