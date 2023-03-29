/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Entity
*/

#include "games/centipede/Entity.hpp"

Arcade::Games::Centipede::Entity::Entity()
{
    _pos = {};
    _size = {0, 0};
    _texture = "";
    _rotation = 0;
}

Arcade::Games::Centipede::Entity::Entity(std::vector<std::pair<float, float>> pos, std::pair<float, float> size, std::string texture, float rotation)
{
    _pos = pos;
    _size = size;
    _texture = texture;
    _rotation = rotation;
}

Arcade::Games::Centipede::Entity::Entity(const Arcade::Games::Centipede::Entity &entity)
{
    _pos = entity.getPosition();
    _size = entity.getSize();
    _texture = entity.getTexture();
    _rotation = entity.getRotation();
}

Arcade::Games::Centipede::Entity::~Entity()
{
}

void Arcade::Games::Centipede::Entity::setPosition(std::vector<std::pair<float, float>> pos)
{
    _pos = pos;
}

std::vector<std::pair<float, float>> Arcade::Games::Centipede::Entity::getPosition() const
{
    return _pos;
}

void Arcade::Games::Centipede::Entity::setSize(std::pair<float, float> size)
{
    _size = size;
}

std::pair<float, float> Arcade::Games::Centipede::Entity::getSize() const
{
    return _size;
}

void Arcade::Games::Centipede::Entity::setTexture(std::string texture)
{
    _texture = texture;
}

std::string Arcade::Games::Centipede::Entity::getTexture() const
{
    return _texture;
}

void Arcade::Games::Centipede::Entity::setRotation(float rotation)
{
    _rotation = rotation;
}

float Arcade::Games::Centipede::Entity::getRotation() const
{
    return _rotation;
}
