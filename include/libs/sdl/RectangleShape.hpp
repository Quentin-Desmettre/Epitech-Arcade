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

/**
 * @brief A rectangle shape, with a size, a position and a color.
 */
class Arcade::Graphics::Sdl::RectangleShape {
public:
    /**
     * @brief Creates a new rectangle shape, with a size of 0, a position of 0,0 and a color of black.
     */
    RectangleShape();

    /**
     * @brief Creates a new rectangle shape.
     * @param size The size of the rectangle.
     * @param position The position of the rectangle.
     * @param fillColor The color of the rectangle.
     */
    RectangleShape(SpriteSize size, SpriteSize position, const SDL_Color &fillColor);

    /**
     * @brief Sets the size of the rectangle.
     * @param size The new size of the rectangle.
     */
    void setSize(const SpriteSize &size);

    /**
     * @brief Sets the position of the rectangle.
     * @param position The new position of the rectangle.
     */
    void setPosition(const SpriteSize &position);

    /**
     * @brief Sets the color of the rectangle.
     * @param fillColor The new color of the rectangle.
     */
    void setFillColor(const SDL_Color &fillColor);

    /**
     * @brief Gets the size of the rectangle.
     * @return The size of the rectangle.
     */
    SpriteSize getSize() const;

    /**
     * @brief Gets the position of the rectangle.
     * @return The position of the rectangle.
     */
    SpriteSize getPosition() const;

    /**
     * @brief Gets the color of the rectangle.
     * @return The color of the rectangle.
     */
    const SDL_Color &getFillColor() const;

private:
    SDL_Rect _rect;
    SDL_Color _color;

};



#endif //EPITECH_ARCADE_RECTANGLESHAPE_HPP
