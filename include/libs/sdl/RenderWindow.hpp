/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** RenderWindow
*/

#ifndef EPITECH_ARCADE_RENDERWINDOW_HPP
#define EPITECH_ARCADE_RENDERWINDOW_HPP
#include <SDL2/SDL.h>
#include "sdl/Sprite.hpp"
#include "sdl/Text.hpp"
#include "sdl/RectangleShape.hpp"

namespace Arcade::Graphics::Sdl {
    class RenderWindow;
} // Sdl

/**
 * @brief A window that can be drawn on.
 */
class Arcade::Graphics::Sdl::RenderWindow {
    public:
        /**
         * @brief Creates a new window.
         * @param width The width of the window.
         * @param height The height of the window.
         */
        RenderWindow(int width, int height);
        ~RenderWindow();

        /**
         * @brief Clears the window.
         */
        void clear();

        /**
         * @brief Draws a sprite on the window.
         * @param sprite The sprite to draw.
         */
        void draw(const Sprite &sprite);

        /**
         * @brief Draws a text on the window.
         * @param text The text to draw.
         */
        void draw(Text &text);

        /**
         * @brief Draws a rectangle on the window.
         * @param rect The rectangle to draw.
         */
        void draw(const RectangleShape &rect);

        /**
         * @brief Draws a line on the window.
         * @param start The start pos of the line.
         * @param end The end pos of the line.
         * @param color The color of the line.
         */
        void drawLine(const SpriteSize &start, const SpriteSize &end, const SDL_Color &color);

        /**
         * @brief Actually renders everything that has been drawn.
         */
        void display();

        /**
         * @brief Gets the SDL2 raw window pointer.
         * @return The SDL2 raw window pointer.
         */
        SDL_Renderer *getRenderer() const;

    private:
        void waitForNextFrame();

        SDL_Window *_window;
        SDL_Renderer *_renderer;
        long _lastFrame;
};

#endif //EPITECH_ARCADE_RENDERWINDOW_HPP
