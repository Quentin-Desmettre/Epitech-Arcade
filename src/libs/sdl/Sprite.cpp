/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Sprite
*/

#include "libs/sdl/Sprite.hpp"

Arcade::Graphics::Sdl::Sprite::Sprite(const Texture &texture):
    _texture(&texture)
{
}

Arcade::Graphics::Sdl::Sprite::Sprite():
    _texture(nullptr)
{
}

void Arcade::Graphics::Sdl::Sprite::setTexture(const Texture &texture)
{
    _texture = &texture;
    setTextureRect({0, 0, _texture->getSize().first, _texture->getSize().second});
    setSize({_texture->getSize().first, _texture->getSize().second});
}

void Arcade::Graphics::Sdl::Sprite::setSize(const SpriteSize &size)
{
    _size = size;
}

void Arcade::Graphics::Sdl::Sprite::setTextureRect(const TextureRect &rect)
{
    _textureRect = rect;
}

void Arcade::Graphics::Sdl::Sprite::setPosition(const SpriteSize &position)
{
    _position = position;
}

const Arcade::Graphics::Sdl::Texture &Arcade::Graphics::Sdl::Sprite::getTexture() const
{
    return *_texture;
}

SpriteSize Arcade::Graphics::Sdl::Sprite::getSize() const
{
    return _size;
}

const Arcade::Graphics::Sdl::TextureRect &Arcade::Graphics::Sdl::Sprite::getTextureRect() const
{
    return _textureRect;
}

const SpriteSize &Arcade::Graphics::Sdl::Sprite::getPosition() const
{
    return _position;
}
