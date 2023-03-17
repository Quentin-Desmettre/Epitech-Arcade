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

namespace Arcade {
    namespace Sdl {
        class RenderWindow;
    } // Arcade
} // Sdl

class Arcade::Sdl::RenderWindow {
    public:
        RenderWindow(int width, int height);
        ~RenderWindow();

        void clear();
        void draw(const Sprite &sprite);
        void draw(Text &text);
        void draw(const RectangleShape &rect);
        void drawLine(const SpriteSize &start, const SpriteSize &end, const SDL_Color &color);

        void display();

        SDL_Renderer *getRenderer() const;

    private:
        void waitForNextFrame();

        SDL_Window *_window;
        SDL_Renderer *_renderer;
        long _lastFrame;
};

#endif //EPITECH_ARCADE_RENDERWINDOW_HPP
