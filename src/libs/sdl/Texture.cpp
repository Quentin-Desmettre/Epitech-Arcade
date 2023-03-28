/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Texture
*/

#include "libs/sdl/Texture.hpp"
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <iostream>

Arcade::Graphics::Sdl::Texture::Texture(const std::string &texturePath, SDL_Renderer *renderer):
    _size({0, 0}),
    _texture(nullptr)
{
    SDL_Surface *surface = IMG_Load(texturePath.c_str());
    if (!surface) {
        std::cerr << "Error: SDL2: Cannot load texture: " << texturePath << std::endl;
        return;
    }

    _size = {surface->w, surface->h};
    _texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!_texture) {
        std::cerr << "Error: SDL2: Cannot create texture: " << texturePath << std::endl;
        return;
    }

    SDL_FreeSurface(surface);
}

Arcade::Graphics::Sdl::Texture::~Texture()
{
    if (_texture)
        SDL_DestroyTexture(_texture);
}

TextureSize Arcade::Graphics::Sdl::Texture::getSize() const
{
    return _size;
}

SDL_Texture *Arcade::Graphics::Sdl::Texture::getRawTexture() const
{
    return _texture;
}
