/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Texture
*/

#ifndef EPITECH_ARCADE_TEXTURE_HPP
#define EPITECH_ARCADE_TEXTURE_HPP
#include <string>
#include <map>
#include <ncurses.h>
#include <vector>

namespace Arcade {
    namespace NCurses {

        class Texture;
        enum Color {
            BLACK = COLOR_BLACK,
            RED = COLOR_RED,
            GREEN = COLOR_GREEN,
            YELLOW = COLOR_YELLOW,
            BLUE = COLOR_BLUE,
            MAGENTA = COLOR_MAGENTA,
            CYAN = COLOR_CYAN,
            WHITE = COLOR_WHITE
        };

    } // Arcade
} // NCurses

class Arcade::NCurses::Texture {
public:
    Texture(const std::string &path, int width, int height);
    ~Texture();

    std::string getContent() const;
    Color getTextColor() const;
    Color getBackgroundColor() const;

    static void createColorPair(Color fg, Color bg);
    static void removeColorPair(Color fg, Color bg);
    short getColorPair() const;
private:
    void fillContent(char c, int width, int height);

    std::string _text;
    Color _bgColor, _textColor;

    static const std::map<std::string, Color> _colorMap;
    static std::map<std::pair<Color, Color>, short> _colorPairs;
    static const char _defaultContent;
    static const Color _defaultBgColor, _defaultTextColor;
    static const std::string _textRegex, _bgColorRegex, _textColorRegex;
    static std::vector<short> _availableColorPairs;
};

#endif //EPITECH_ARCADE_TEXTURE_HPP
