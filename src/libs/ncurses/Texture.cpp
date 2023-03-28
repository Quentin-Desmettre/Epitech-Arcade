/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Texture
*/

#include "Texture.hpp"
#include <fstream>
#include <regex>
#include <iostream>
/*
 *
 *
 * Format of a texture:
 *
 * text: <single char>
 * bg-color: <color>
 * text-color: <color>
 *
 * Color must be among the following:
 *  - black
 *  - red
 *  - green
 *  - yellow
 *  - blue
 *  - magenta
 *  - cyan
 *  - white
 *  - none
 */

const std::map<std::string, Arcade::Graphics::NCurses::Color> Arcade::Graphics::NCurses::Texture::_colorMap = {
    {"black", BLACK},
    {"red", RED},
    {"green", GREEN},
    {"yellow", YELLOW},
    {"blue", BLUE},
    {"magenta", MAGENTA},
    {"cyan", CYAN},
    {"white", WHITE}
};

const char Arcade::Graphics::NCurses::Texture::_defaultContent = '#';
const Arcade::Graphics::NCurses::Color Arcade::Graphics::NCurses::Texture::_defaultBgColor = BLACK;
const Arcade::Graphics::NCurses::Color Arcade::Graphics::NCurses::Texture::_defaultTextColor = WHITE;
const std::string Arcade::Graphics::NCurses::Texture::_textRegex = "^text: .$";
const std::string Arcade::Graphics::NCurses::Texture::_bgColorRegex = "^bg-color: (black|red|green|yellow|blue|magenta|cyan|white|none)$";
const std::string Arcade::Graphics::NCurses::Texture::_textColorRegex = "^text-color: (black|red|green|yellow|blue|magenta|cyan|white|none)$";
std::vector<short> Arcade::Graphics::NCurses::Texture::_availableColorPairs;
std::map<std::pair<Arcade::Graphics::NCurses::Color, Arcade::Graphics::NCurses::Color>, short>Arcade::Graphics::NCurses::Texture:: _colorPairs = {};

Arcade::Graphics::NCurses::Texture::Texture(const std::string &path, int width, int height):
    _bgColor(_defaultBgColor), _textColor(_defaultTextColor)
{
    if (_availableColorPairs.empty() && _colorPairs.empty())
        for (int i = COLOR_PAIRS - 1; i > 0; i--)
            _availableColorPairs.push_back(static_cast<short>(i));

    std::ifstream reader(path);
    std::string line;
    char c = _defaultContent;

    _width = width;
    _height = height;
    if (!reader) {
        fillContent(_defaultContent, width, height);
        _hasUsedColorPair = Texture::createColorPair(_textColor, _bgColor);
        return;
    }
    while (std::getline(reader, line)) {
        if (std::regex_match(line, std::regex(_textRegex)))
            c = line.substr(6)[0];
        else if (std::regex_match(line, std::regex(_bgColorRegex)))
            _bgColor = _colorMap.at(line.substr(10));
        else if (std::regex_match(line, std::regex(_textColorRegex)))
            _textColor = _colorMap.at(line.substr(12));
    }
    fillContent(c, width, height);
    _hasUsedColorPair = Texture::createColorPair(_textColor, _bgColor);
}

Arcade::Graphics::NCurses::Texture::~Texture()
{
    if (_hasUsedColorPair)
        Texture::removeColorPair(_textColor, _bgColor);
}

void Arcade::Graphics::NCurses::Texture::fillContent(char c, int width, int height)
{
    std::ostringstream oss;

    for (int i = 0; i < height; i++) {
        oss << std::string(width, c);
        if (i != height - 1)
            oss << std::endl;
    }
    _c = c;
    _text = oss.str();
}

std::string Arcade::Graphics::NCurses::Texture::getContent() const
{
    return _text;
}

Arcade::Graphics::NCurses::Color Arcade::Graphics::NCurses::Texture::getTextColor() const
{
    return _textColor;
}

Arcade::Graphics::NCurses::Color Arcade::Graphics::NCurses::Texture::getBackgroundColor() const
{
    return _bgColor;
}

bool Arcade::Graphics::NCurses::Texture::createColorPair(Color fg, Color bg)
{
    if (_colorPairs.find({fg, bg}) != _colorPairs.end())
        return false;

    short pair = _availableColorPairs.back();
    init_pair(pair, fg, bg);
    _colorPairs[{fg, bg}] = pair;
    _availableColorPairs.pop_back();
    return true;
}

void Arcade::Graphics::NCurses::Texture::removeColorPair(Color fg, Color bg)
{
    if (_colorPairs.find({fg, bg}) == _colorPairs.end())
        return;
    _availableColorPairs.push_back(_colorPairs[{fg, bg}]);
    _colorPairs.erase({fg, bg});
}

short Arcade::Graphics::NCurses::Texture::getColorPair() const
{
    if (_colorPairs.find({_textColor, _bgColor}) == _colorPairs.end())
        return -1;
    return _colorPairs[{_textColor, _bgColor}];
}

void Arcade::Graphics::NCurses::Texture::setSize(int width, int height)
{
    _width = width;
    _height = height;
    fillContent(_c, width, height);
}

void Arcade::Graphics::NCurses::Texture::setTextColor(Color color)
{
    if (_hasUsedColorPair)
        removeColorPair(_textColor, _bgColor);
    _textColor = color;
    _hasUsedColorPair = Texture::createColorPair(_textColor, _bgColor);
}

void Arcade::Graphics::NCurses::Texture::setBackgroundColor(Color color)
{
    if (_hasUsedColorPair)
        removeColorPair(_textColor, _bgColor);
    _bgColor = color;
    _hasUsedColorPair = Texture::createColorPair(_textColor, _bgColor);
}

void Arcade::Graphics::NCurses::Texture::setContent(char c)
{
    fillContent(c, _width, _height);
}
