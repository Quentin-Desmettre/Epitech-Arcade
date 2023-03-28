/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Text
*/

#include "libs/sdl/Text.hpp"
#include <SDL2/SDL.h>
#include <iostream>

Arcade::Graphics::Sdl::Text::Text(SDL_Renderer *renderer,
                        const Font *font,
                        const std::string &text,
                        SDL_Color color):
    Arcade::Graphics::Sdl::Sprite(),
    _font(font),
    _text(text),
    _color(color),
    _isSurfaceUpdated(false),
    _surface(nullptr),
    _texture(nullptr),
    _renderer(renderer)
{
}

Arcade::Graphics::Sdl::Text::~Text()
{
    if (_surface)
        SDL_FreeSurface(_surface);
    if (_texture)
        SDL_DestroyTexture(_texture);
}

void Arcade::Graphics::Sdl::Text::setText(const std::string &text)
{
    _text = text;
    _isSurfaceUpdated = false;
    _size = {0, 0};
}

void Arcade::Graphics::Sdl::Text::setFont(const Font &font)
{
    _font = &font;
    _isSurfaceUpdated = false;
    _size = {0, 0};
}

void Arcade::Graphics::Sdl::Text::setColor(SDL_Color color)
{
    _color = color;
    _isSurfaceUpdated = false;
    _size = {0, 0};
}

SDL_Texture *Arcade::Graphics::Sdl::Text::getRawTexture()
{
    if (_isSurfaceUpdated)
        return _texture;

    if (_surface)
        SDL_FreeSurface(_surface);
    if (_texture)
        SDL_DestroyTexture(_texture);
    _surface = _font->getRawFont() ? TTF_RenderText_Solid(_font->getRawFont(), _text.c_str(), _color) : nullptr;
    _texture = _surface ? SDL_CreateTextureFromSurface(_renderer, _surface) : nullptr;
    if (!_texture) {
        std::cerr << "Error: SDL2: Cannot create texture from surface" << SDL_GetError() << std::endl;
        return nullptr;
    }
    _isSurfaceUpdated = true;
    return _texture;
}

SpriteSize Arcade::Graphics::Sdl::Text::getSize() const
{
    if (!_surface)
        return {0, 0};
    return {_surface->w, _surface->h};
}
