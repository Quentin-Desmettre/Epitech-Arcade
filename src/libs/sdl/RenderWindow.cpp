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
#include <iostream>

int Arcade::Sdl::RenderWindow::_nbInstances = 0;

void Arcade::Sdl::RenderWindow::initSdl()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error("Error: SDL2: Failed to init SDL.");
    if (TTF_Init() < 0)
        throw std::runtime_error("Error: SDL2: Failed to init SDL_ttf.");
    std::cerr << "Info: SDL2: Init SDL." << std::endl;
}

Arcade::Sdl::RenderWindow::RenderWindow(int width, int height)
{
    _lastFrame = 0;
    _nbInstances++;
    if (!SDL_WasInit(SDL_INIT_EVERYTHING))
        initSdl();
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    _renderer = _window ? SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED) : nullptr;

    if (!_window || !_renderer)
        throw std::runtime_error("Error: SDL2: Failed to create window.");
}

Arcade::Sdl::RenderWindow::~RenderWindow()
{
    _nbInstances--;
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    if (!_nbInstances)
        SDL_Quit();
}

void Arcade::Sdl::RenderWindow::draw(const Sprite &sprite)
{
    SDL_Rect destRect = {
            .x = sprite.getPosition().first,
            .y = sprite.getPosition().second,
            .w = sprite.getSize().first,
            .h = sprite.getSize().second
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

void Arcade::Sdl::RenderWindow::draw(Text &text)
{
    text.getRawTexture();
    SDL_Rect destRect = {
            .x = text.getPosition().first,
            .y = text.getPosition().second,
            .w = text.getSize().first,
            .h = text.getSize().second
    };
    if (text.getRawTexture())
        SDL_RenderCopy(_renderer, text.getRawTexture(), nullptr, &destRect);
}

void Arcade::Sdl::RenderWindow::draw(const RectangleShape &rect)
{
    // Save old color
    SDL_Color baseColor;
    SDL_GetRenderDrawColor(_renderer, &baseColor.r, &baseColor.g, &baseColor.b, &baseColor.a);

    // Draw rect
    SDL_Rect destRect = {
            .x = rect.getPosition().first,
            .y = rect.getPosition().second,
            .w = rect.getSize().first,
            .h = rect.getSize().second
    };
    SDL_SetRenderDrawColor(_renderer, rect.getFillColor().r, rect.getFillColor().g, rect.getFillColor().b, rect.getFillColor().a);
    SDL_RenderFillRect(_renderer, &destRect);

    // Restore old color
    SDL_SetRenderDrawColor(_renderer, baseColor.r, baseColor.g, baseColor.b, baseColor.a);
}

void Arcade::Sdl::RenderWindow::drawLine(const SpriteSize &start, const SpriteSize &end, const SDL_Color &color)
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

SDL_Renderer *Arcade::Sdl::RenderWindow::getRenderer() const
{
    return _renderer;
}

void Arcade::Sdl::RenderWindow::clear()
{
    SDL_RenderClear(_renderer);
}

void Arcade::Sdl::RenderWindow::display()
{
    waitForNextFrame();
    SDL_RenderPresent(_renderer);
}

void Arcade::Sdl::RenderWindow::waitForNextFrame()
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
