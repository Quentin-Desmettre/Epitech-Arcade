/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** RectangleShape
*/

#include "libs/sdl/RectangleShape.hpp"

Arcade::Sdl::RectangleShape::RectangleShape():
    RectangleShape({0, 0}, {0, 0}, {0, 0, 0, 0})
{
}

Arcade::Sdl::RectangleShape::RectangleShape(SpriteSize size, SpriteSize position, const SDL_Color &fillColor)
{
    setSize(size);
    setPosition(position);
    setFillColor(fillColor);
}

void Arcade::Sdl::RectangleShape::setSize(const SpriteSize &size)
{
    _rect.w = size.first;
    _rect.h = size.second;
}

void Arcade::Sdl::RectangleShape::setPosition(const SpriteSize &position)
{
    _rect.x = position.first;
    _rect.y = position.second;
}

void Arcade::Sdl::RectangleShape::setFillColor(const SDL_Color &fillColor)
{
    _color = fillColor;
}

SpriteSize Arcade::Sdl::RectangleShape::getSize() const
{
    return {_rect.w, _rect.h};
}

SpriteSize Arcade::Sdl::RectangleShape::getPosition() const
{
    return {_rect.x, _rect.y};
}

const SDL_Color &Arcade::Sdl::RectangleShape::getFillColor() const
{
    return _color;
}
