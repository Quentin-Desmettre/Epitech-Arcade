/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** utils
*/

#include <cstdio>
#include <iostream>
#include "Sfml.hpp"

void Arcade::Graphics::SFML::SFML::calculateCellSize(int width, int height)
{
    float cellSizeX = _window.getSize().x / width;
    float cellSizeY = _window.getSize().y / height;

    _cellSize = cellSizeX < cellSizeY ? cellSizeX : cellSizeY;
}

void Arcade::Graphics::SFML::SFML::centerTextOrigin()
{
    _text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height / 2);
}

void Arcade::Graphics::SFML::SFML::drawTextWithColor(sf::Color color)
{
    _text.setFillColor(color);
    _window.draw(_text);
    _text.setFillColor(sf::Color::White);
}

void Arcade::Graphics::SFML::SFML::drawRect(sf::Vector2f size, sf::Vector2f position)
{
    _rectangle.setSize(size);
    _rectangle.setPosition(position);
    _window.draw(_rectangle);
}

void Arcade::Graphics::SFML::SFML::drawLine(sf::Vector2f start, sf::Vector2f end)
{
    sf::Vertex line[] = {
        sf::Vertex(start, sf::Color::White),
        sf::Vertex(end, sf::Color::White)
    };
    _window.draw(line, 2, sf::Lines);
}

bool Arcade::Graphics::SFML::SFML::loadTexture(std::string texturePath)
{
    if (_textureMap.find(texturePath) == _textureMap.end()) {
        if (_texture.loadFromFile(texturePath) == false) {
            std::cerr << "Error: Cannot load texture: " << texturePath << std::endl;
            return false;
        }
        _textureMap[texturePath] = std::make_unique<sf::Texture>(_texture);
    }
    return true;
}
