/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Sprite
*/

#include "libs/sdl/Sprite.hpp"

Arcade::Sdl::Sprite::Sprite(const Texture &texture):
    _texture(&texture)
{
}

Arcade::Sdl::Sprite::Sprite():
    _texture(nullptr)
{
}

void Arcade::Sdl::Sprite::setTexture(const Texture &texture)
{
    _texture = &texture;
    setTextureRect({0, 0, _texture->getSize().first, _texture->getSize().second});
}

void Arcade::Sdl::Sprite::setSize(const SpriteSize &size)
{
    _size = size;
}

void Arcade::Sdl::Sprite::setTextureRect(const TextureRect &rect)
{
    _textureRect = rect;
    _size = {rect.width, rect.height};
}

void Arcade::Sdl::Sprite::setPosition(const SpriteSize &position)
{
    _position = position;
}

const Arcade::Sdl::Texture &Arcade::Sdl::Sprite::getTexture() const
{
    return *_texture;
}

SpriteSize Arcade::Sdl::Sprite::getSize() const
{
    return _size;
}

const Arcade::Sdl::TextureRect &Arcade::Sdl::Sprite::getTextureRect() const
{
    return _textureRect;
}

const SpriteSize &Arcade::Sdl::Sprite::getPosition() const
{
    return _position;
}
