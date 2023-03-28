/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Font
*/

#include "sdl/Font.hpp"
#include <iostream>

Arcade::Graphics::Sdl::Font::Font(const std::string &fontPath, int fontSize, bool bold):
    _font(nullptr)
{
    _font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!_font)
        std::cerr << "Error: SDL2: Cannot open font: " << fontPath << std::endl;
    else if (bold)
        TTF_SetFontStyle(_font, TTF_STYLE_BOLD);
}

Arcade::Graphics::Sdl::Font::~Font()
{
    if (_font)
        TTF_CloseFont(_font);
}

TTF_Font *Arcade::Graphics::Sdl::Font::getRawFont() const
{
    return _font;
}
