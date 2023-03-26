/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Entity
*/

#include "games/centipede/Entity.hpp"

Arcade::Centipede::Entity::Entity()
{
    _pos = {};
    _size = {0, 0};
    _texture = "";
    _rotation = 0;
}

Arcade::Centipede::Entity::Entity(std::vector<std::pair<float, float>> pos, std::pair<float, float> size, std::string texture, float rotation)
{
    _pos = pos;
    _size = size;
    _texture = texture;
    _rotation = rotation;
}

Arcade::Centipede::Entity::Entity(const Arcade::Centipede::Entity &entity)
{
    _pos = entity.getPosition();
    _size = entity.getSize();
    _texture = entity.getTexture();
    _rotation = entity.getRotation();
}

Arcade::Centipede::Entity::~Entity()
{
}

void Arcade::Centipede::Entity::setPosition(std::vector<std::pair<float, float>> pos)
{
    _pos = pos;
}

std::vector<std::pair<float, float>> Arcade::Centipede::Entity::getPosition() const
{
    return _pos;
}

void Arcade::Centipede::Entity::setSize(std::pair<float, float> size)
{
    _size = size;
}

std::pair<float, float> Arcade::Centipede::Entity::getSize() const
{
    return _size;
}

void Arcade::Centipede::Entity::setTexture(std::string texture)
{
    _texture = texture;
}

std::string Arcade::Centipede::Entity::getTexture() const
{
    return _texture;
}

void Arcade::Centipede::Entity::setRotation(float rotation)
{
    _rotation = rotation;
}

float Arcade::Centipede::Entity::getRotation() const
{
    return _rotation;
}
