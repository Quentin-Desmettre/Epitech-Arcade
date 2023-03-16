/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** main
*/

#include <cstdio>
#include <iostream>
#include "Sfml.hpp"

extern "C"
{
    void *createDisplay() {
        return new Arcade::SFML();
    }

    void deleteDisplay(void *display) {
        delete reinterpret_cast<Arcade::SFML *>(display);
    }
}

Arcade::SFML::SFML()
{
    _window.create(sf::VideoMode(1000, 1000), "Arcade");
    _window.setFramerateLimit(60);
    _font.loadFromFile("assets/arial.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(24);
    _text.setFillColor(sf::Color::White);
    _text.setStyle(sf::Text::Bold);
}

Arcade::SFML::~SFML()
{
    _window.close();
}

std::vector<Arcade::Key> Arcade::SFML::getPressedKeys()
{
    std::vector<Arcade::Key> keys;

    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Escape:
                    keys.push_back(Arcade::Key::Escape);
                    break;
                case sf::Keyboard::Up:
                    keys.push_back(Arcade::Key::Up);
                    break;
                case sf::Keyboard::Down:
                    keys.push_back(Arcade::Key::Down);
                    break;
                case sf::Keyboard::Left:
                    keys.push_back(Arcade::Key::Left);
                    break;
                case sf::Keyboard::Right:
                    keys.push_back(Arcade::Key::Right);
                    break;
                case sf::Keyboard::Return:
                    keys.push_back(Arcade::Key::Enter);
                    break;
                case sf::Keyboard::Space:
                    keys.push_back(Arcade::Key::Space);
                    break;
                default:
                    break;
            }
        }
    }
    return keys;
}

void Arcade::SFML::calculateCellSize(int width, int height)
{
    float cellSizeX = _window.getSize().x / width;
    float cellSizeY = _window.getSize().y / height;

    _cellSize = cellSizeX < cellSizeY ? cellSizeX : cellSizeY;
}

void Arcade::SFML::centerTextOrigin()
{
    _text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height / 2);
}

void Arcade::SFML::drawTextWithColor(sf::Color color)
{
    _text.setFillColor(color);
    _window.draw(_text);
    _text.setFillColor(sf::Color::White);
}

void Arcade::SFML::render(Arcade::IGameData &gameData)
{
    std::vector<IEntity *> entities = gameData.getEntities();

    _window.clear();
    calculateCellSize(gameData.getMapSize().first, gameData.getMapSize().second);

    for (auto &entity : entities) {
        // std::cout << "test:" << entity.getTexture() << std::endl;
        if (_textureMap.find(entity->getTexture()) == _textureMap.end()) {
            if (_texture.loadFromFile(entity->getTexture()) == false) {
                std::cerr << "Error: Cannot load texture: " << entity->getTexture() << std::endl;
                continue;
            }
            _textureMap[entity->getTexture()] = std::make_unique<sf::Texture>(_texture);
        }
        _sprite.setTexture(*_textureMap[entity->getTexture()].get());
        _sprite.scale(_sprite.getLocalBounds().width / _cellSize, _sprite.getLocalBounds().height / _cellSize);
        _sprite.scale(entity->getSize().first, entity->getSize().second);
        _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
        _sprite.setPosition(entity->getPosition().first * _cellSize, entity->getPosition().second * _cellSize);
        _sprite.setRotation(entity->getRotation());
        _window.draw(_sprite);
    }
    _text.setString(gameData.getGameName());
    _text.setPosition(0, 0);
    _window.draw(_text);
    _window.display();
}

void Arcade::SFML::renderMenu(const std::vector<std::string> &games,
const std::vector<std::string> &graphics, bool isSelectingGame, int selectedIndex)
{
    _window.clear();
    _text.setString("Arcade");
    _text.setCharacterSize(75);
    _text.setPosition(500, 100);
    centerTextOrigin();
    drawTextWithColor(sf::Color::White);
    _text.setCharacterSize(24);
    for (size_t i = 0; i < games.size(); i++) {
        _text.setString(games[i]);
        _text.setPosition(350, 450 + i * 30);
        centerTextOrigin();
        drawTextWithColor(i == selectedIndex && isSelectingGame ?
        sf::Color::Red : sf::Color::White);
    }
    for (size_t i = 0; i < graphics.size(); i++) {
        _text.setString(graphics[i]);
        _text.setPosition(650, 450 + i * 30);
        centerTextOrigin();
        drawTextWithColor(i == selectedIndex && !isSelectingGame ?
        sf::Color::Red : sf::Color::White);
    }
    _window.display();
}
