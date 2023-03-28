/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** RenderWindow
*/

#include "sdl/RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <chrono>
#include <thread>

Arcade::Graphics::Sdl::RenderWindow::RenderWindow(int width, int height)
{
    _lastFrame = 0;
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    _renderer = _window ? SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED) : nullptr;

    if (!_window || !_renderer)
        throw std::runtime_error("Error: SDL2: Failed to create window.");
}

Arcade::Graphics::Sdl::RenderWindow::~RenderWindow()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void Arcade::Graphics::Sdl::RenderWindow::draw(const Sprite &sprite)
{
    SDL_Rect destRect = {
            .x = static_cast<int>(sprite.getPosition().first),
            .y = static_cast<int>(sprite.getPosition().second),
            .w = static_cast<int>(sprite.getSize().first),
            .h = static_cast<int>(sprite.getSize().second)
    };
    SDL_Rect srcRect = {
            .x = sprite.getTextureRect().left,
            .y = sprite.getTextureRect().top,
            .w = sprite.getTextureRect().width,
            .h = sprite.getTextureRect().height
    };

    if (sprite.getTexture().getRawTexture()) {
        SDL_RenderCopy(_renderer, sprite.getTexture().getRawTexture(), &srcRect, &destRect);
    }
}

void Arcade::Graphics::Sdl::RenderWindow::draw(Text &text)
{
    text.getRawTexture();
    SDL_Rect destRect = {
            .x = static_cast<int>(text.getPosition().first),
            .y = static_cast<int>(text.getPosition().second),
            .w = static_cast<int>(text.getSize().first),
            .h = static_cast<int>(text.getSize().second)
    };
    if (text.getRawTexture())
        SDL_RenderCopy(_renderer, text.getRawTexture(), nullptr, &destRect);
}

void Arcade::Graphics::Sdl::RenderWindow::draw(const RectangleShape &rect)
{
    // Save old color
    SDL_Color baseColor;
    SDL_GetRenderDrawColor(_renderer, &baseColor.r, &baseColor.g, &baseColor.b, &baseColor.a);

    // Draw rect
    SDL_Rect destRect = {
            .x = static_cast<int>(rect.getPosition().first),
            .y = static_cast<int>(rect.getPosition().second),
            .w = static_cast<int>(rect.getSize().first),
            .h = static_cast<int>(rect.getSize().second)
    };
    SDL_SetRenderDrawColor(_renderer, rect.getFillColor().r, rect.getFillColor().g, rect.getFillColor().b, rect.getFillColor().a);
    SDL_RenderFillRect(_renderer, &destRect);

    // Restore old color
    SDL_SetRenderDrawColor(_renderer, baseColor.r, baseColor.g, baseColor.b, baseColor.a);
}

void Arcade::Graphics::Sdl::RenderWindow::drawLine(const SpriteSize &start, const SpriteSize &end, const SDL_Color &color)
{
    // Save old color
    SDL_Color baseColor;
    SDL_GetRenderDrawColor(_renderer, &baseColor.r, &baseColor.g, &baseColor.b, &baseColor.a);

    // Draw line
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(_renderer, start.first, start.second, end.first, end.second);

    // Restore old color
    SDL_SetRenderDrawColor(_renderer, baseColor.r, baseColor.g, baseColor.b, baseColor.a);
}

SDL_Renderer *Arcade::Graphics::Sdl::RenderWindow::getRenderer() const
{
    return _renderer;
}

void Arcade::Graphics::Sdl::RenderWindow::clear()
{
    SDL_RenderClear(_renderer);
}

void Arcade::Graphics::Sdl::RenderWindow::display()
{
    waitForNextFrame();
    SDL_RenderPresent(_renderer);
}

void Arcade::Graphics::Sdl::RenderWindow::waitForNextFrame()
{
    long now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();
    if (now - _lastFrame < 1000 / 60)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60 - (now - _lastFrame)));

    _lastFrame = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();
}
