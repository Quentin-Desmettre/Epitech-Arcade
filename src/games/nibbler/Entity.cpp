/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Entity
*/

#include "games/nibbler/Entity.hpp"

Arcade::Nibbler::Entity::Entity()
{
    _pos = {};
    _size = {0, 0};
    _texture = "";
    _rotation = 0;
}

Arcade::Nibbler::Entity::Entity(std::vector<std::pair<float, float>> pos, std::pair<float, float> size, std::string texture, float rotation)
{
    _pos = pos;
    _size = size;
    _texture = texture;
    _rotation = rotation;
}

Arcade::Nibbler::Entity::Entity(const Arcade::Nibbler::Entity &entity)
{
    _pos = entity.getPosition();
    _size = entity.getSize();
    _texture = entity.getTexture();
    _rotation = entity.getRotation();
}

Arcade::Nibbler::Entity::~Entity()
{
}

void Arcade::Nibbler::Entity::setPosition(std::vector<std::pair<float, float>> pos)
{
    _pos = pos;
}

std::vector<std::pair<float, float>> Arcade::Nibbler::Entity::getPosition() const
{
    return _pos;
}

void Arcade::Nibbler::Entity::setSize(std::pair<float, float> size)
{
    _size = size;
}

std::pair<float, float> Arcade::Nibbler::Entity::getSize() const
{
    return _size;
}

void Arcade::Nibbler::Entity::setTexture(std::string texture)
{
    _texture = texture;
}

std::string Arcade::Nibbler::Entity::getTexture() const
{
    return _texture;
}

void Arcade::Nibbler::Entity::setRotation(float rotation)
{
    _rotation = rotation;
}

float Arcade::Nibbler::Entity::getRotation() const
{
    return _rotation;
}
