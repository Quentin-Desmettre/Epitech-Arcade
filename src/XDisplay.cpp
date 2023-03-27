/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** XDisplay
*/

#include "XDisplay.hpp"
#include <iostream>

#include <fstream>

Display *Arcade::XDisplay::display = nullptr;

KeySym Arcade::XDisplay::keyToKeySym(Arcade::Key key)
{
    switch (key) {
        case Arcade::Key::LShift:     return XK_Shift_L;
        case Arcade::Key::RShift:     return XK_Shift_R;
        case Arcade::Key::LControl:   return XK_Control_L;
        case Arcade::Key::RControl:   return XK_Control_R;
        case Arcade::Key::LAlt:       return XK_Alt_L;
        case Arcade::Key::RAlt:       return XK_Alt_R;
        case Arcade::Key::LSystem:    return XK_Super_L;
        case Arcade::Key::RSystem:    return XK_Super_R;
        case Arcade::Key::Menu:       return XK_Menu;
        case Arcade::Key::Escape:     return XK_Escape;
        case Arcade::Key::Semicolon:  return XK_semicolon;
        case Arcade::Key::Slash:      return XK_slash;
        case Arcade::Key::Equal:      return XK_equal;
        case Arcade::Key::Hyphen:     return XK_minus;
        case Arcade::Key::LBracket:   return XK_bracketleft;
        case Arcade::Key::RBracket:   return XK_bracketright;
        case Arcade::Key::Comma:      return XK_comma;
        case Arcade::Key::Period:     return XK_period;
        case Arcade::Key::Apostrophe: return XK_apostrophe;
        case Arcade::Key::Backslash:  return XK_backslash;
        case Arcade::Key::Grave:      return XK_grave;
        case Arcade::Key::Space:      return XK_space;
        case Arcade::Key::Enter:      return XK_Return;
        case Arcade::Key::Backspace:  return XK_BackSpace;
        case Arcade::Key::Tab:        return XK_Tab;
        case Arcade::Key::PageUp:     return XK_Prior;
        case Arcade::Key::PageDown:   return XK_Next;
        case Arcade::Key::End:        return XK_End;
        case Arcade::Key::Home:       return XK_Home;
        case Arcade::Key::Insert:     return XK_Insert;
        case Arcade::Key::Delete:     return XK_Delete;
        case Arcade::Key::Add:        return XK_KP_Add;
        case Arcade::Key::Subtract:   return XK_KP_Subtract;
        case Arcade::Key::Multiply:   return XK_KP_Multiply;
        case Arcade::Key::Divide:     return XK_KP_Divide;
        case Arcade::Key::Pause:      return XK_Pause;
        case Arcade::Key::F1:         return XK_F1;
        case Arcade::Key::F2:         return XK_F2;
        case Arcade::Key::F3:         return XK_F3;
        case Arcade::Key::F4:         return XK_F4;
        case Arcade::Key::F5:         return XK_F5;
        case Arcade::Key::F6:         return XK_F6;
        case Arcade::Key::F7:         return XK_F7;
        case Arcade::Key::F8:         return XK_F8;
        case Arcade::Key::F9:         return XK_F9;
        case Arcade::Key::F10:        return XK_F10;
        case Arcade::Key::F11:        return XK_F11;
        case Arcade::Key::F12:        return XK_F12;
        case Arcade::Key::F13:        return XK_F13;
        case Arcade::Key::F14:        return XK_F14;
        case Arcade::Key::F15:        return XK_F15;
        case Arcade::Key::Left:       return XK_Left;
        case Arcade::Key::Right:      return XK_Right;
        case Arcade::Key::Up:         return XK_Up;
        case Arcade::Key::Down:       return XK_Down;
        case Arcade::Key::Numpad0:    return XK_KP_Insert;
        case Arcade::Key::Numpad1:    return XK_KP_End;
        case Arcade::Key::Numpad2:    return XK_KP_Down;
        case Arcade::Key::Numpad3:    return XK_KP_Page_Down;
        case Arcade::Key::Numpad4:    return XK_KP_Left;
        case Arcade::Key::Numpad5:    return XK_KP_Begin;
        case Arcade::Key::Numpad6:    return XK_KP_Right;
        case Arcade::Key::Numpad7:    return XK_KP_Home;
        case Arcade::Key::Numpad8:    return XK_KP_Up;
        case Arcade::Key::Numpad9:    return XK_KP_Page_Up;
        case Arcade::Key::A:          return XK_a;
        case Arcade::Key::B:          return XK_b;
        case Arcade::Key::C:          return XK_c;
        case Arcade::Key::D:          return XK_d;
        case Arcade::Key::E:          return XK_e;
        case Arcade::Key::F:          return XK_f;
        case Arcade::Key::G:          return XK_g;
        case Arcade::Key::H:          return XK_h;
        case Arcade::Key::I:          return XK_i;
        case Arcade::Key::J:          return XK_j;
        case Arcade::Key::K:          return XK_k;
        case Arcade::Key::L:          return XK_l;
        case Arcade::Key::M:          return XK_m;
        case Arcade::Key::N:          return XK_n;
        case Arcade::Key::O:          return XK_o;
        case Arcade::Key::P:          return XK_p;
        case Arcade::Key::Q:          return XK_q;
        case Arcade::Key::R:          return XK_r;
        case Arcade::Key::S:          return XK_s;
        case Arcade::Key::T:          return XK_t;
        case Arcade::Key::U:          return XK_u;
        case Arcade::Key::V:          return XK_v;
        case Arcade::Key::W:          return XK_w;
        case Arcade::Key::X:          return XK_x;
        case Arcade::Key::Y:          return XK_y;
        case Arcade::Key::Z:          return XK_z;
        case Arcade::Key::Num0:       return XK_0;
        case Arcade::Key::Num1:       return XK_1;
        case Arcade::Key::Num2:       return XK_2;
        case Arcade::Key::Num3:       return XK_3;
        case Arcade::Key::Num4:       return XK_4;
        case Arcade::Key::Num5:       return XK_5;
        case Arcade::Key::Num6:       return XK_6;
        case Arcade::Key::Num7:       return XK_7;
        case Arcade::Key::Num8:       return XK_8;
        case Arcade::Key::Num9:       return XK_9;
        default:                   return NoSymbol;
    }
}

KeyCode Arcade::XDisplay::keyToKeyCode(Arcade::Key key)
{
    KeySym keysym = keyToKeySym(key);

    if (keysym != NoSymbol) {
        KeyCode  keycode = XKeysymToKeycode(display, keysym);
        if (keycode != 0)
            return keycode;
    }
    return Arcade::Key::Unknown;
}

Display *Arcade::XDisplay::getDisplay()
{
    if (display == nullptr)
        display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Failed to open X11 display; make sure the DISPLAY environment variable is set correctly" << std::endl;
        std::abort();
    }
    return display;
}

void Arcade::XDisplay::closeDisplay()
{
    if (display != nullptr)
        XCloseDisplay(display);
}

void Arcade::XDisplay::getKeyboardState(char *state)
{
    XQueryKeymap(display, state);
}

bool Arcade::XDisplay::isKeyPressed(Arcade::Key code)
{
    KeyCode keycode = keyToKeyCode(code);
    char keys[32];

    if (!keycode)
        return false;
    getKeyboardState(keys);
    return (keys[keycode / 8] & (1 << (keycode % 8))) != 0;
}

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
