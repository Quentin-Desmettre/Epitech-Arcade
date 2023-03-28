/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** RectangleShape
*/

#ifndef EPITECH_ARCADE_RECTANGLESHAPE_HPP
#define EPITECH_ARCADE_RECTANGLESHAPE_HPP
#include "sdl/Sprite.hpp"

namespace Arcade::Graphics::Sdl {
        class RectangleShape;
    } // Sdl

class Arcade::Graphics::Sdl::RectangleShape {
public:
    RectangleShape();
    RectangleShape(SpriteSize size, SpriteSize position, const SDL_Color &fillColor);

    void setSize(const SpriteSize &size);
    void setPosition(const SpriteSize &position);
    void setFillColor(const SDL_Color &fillColor);

    SpriteSize getSize() const;
    SpriteSize getPosition() const;
    const SDL_Color &getFillColor() const;

private:
    SDL_Rect _rect;
    SDL_Color _color;

};



#endif //EPITECH_ARCADE_RECTANGLESHAPE_HPP
