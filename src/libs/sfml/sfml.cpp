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
    _window.create(sf::VideoMode(1280, 832), "Arcade");
    _window.setFramerateLimit(60);
    _font.loadFromFile("assets/arial.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(24);
    _text.setFillColor(sf::Color::White);
    _text.setStyle(sf::Text::Bold);
    _rectangle.setFillColor(sf::Color::Black);
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

void Arcade::SFML::drawRect(sf::Vector2f size, sf::Vector2f position)
{
    _rectangle.setSize(size);
    _rectangle.setPosition(position);
    _window.draw(_rectangle);
}

void Arcade::SFML::drawLine(sf::Vector2f start, sf::Vector2f end)
{
    sf::Vertex line[] = {
        sf::Vertex(start, sf::Color::White),
        sf::Vertex(end, sf::Color::White)
    };
    _window.draw(line, 2, sf::Lines);
}

bool Arcade::SFML::loadTexture(std::string texturePath)
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

void Arcade::SFML::render(Arcade::IGameData &gameData)
{
    std::vector<IEntity *> entities = gameData.getEntities();

    _window.clear();
    calculateCellSize(gameData.getMapSize().first, gameData.getMapSize().second);

    for (auto &entity : entities) {
        if (loadTexture("assets/" + gameData.getGameName() + "/sfml/" + entity->getTexture()) == false)
            continue;
        _sprite.setTexture(*_textureMap["assets/" + gameData.getGameName() + "/sfml/" + entity->getTexture()].get());
        // _sprite.scale(_sprite.getLocalBounds().width / _cellSize, _sprite.getLocalBounds().height / _cellSize);
        // _sprite.scale(entity->getSize().first, entity->getSize().second);
        _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
        _sprite.setPosition(entity->getPosition().first * _cellSize, entity->getPosition().second * _cellSize);
        _sprite.setRotation(entity->getRotation());
        _window.draw(_sprite);
    }
    // _text.setString(gameData.getGameName());
    // _text.setPosition(0, 0);
    // _window.draw(_text);
    _window.display();
}

void Arcade::SFML::renderMenu(const std::vector<std::string> &games,
const std::vector<std::string> &graphics, int selectedGame, int selectedGraph, const ControlMap &map)
{
    std::vector<std::string> controls;

    _window.clear();
    if (loadTexture("assets/menubg.png") == false)
        return;
    _sprite.setTexture(*_textureMap["assets/menubg.png"].get());
    _window.draw(_sprite);
    drawRect({248, 475}, {887, 291});
    drawRect({248, 475}, {516, 291});
    drawRect({248 + 70, 475}, {80, 291});
    drawLine({532, 350}, {532 + 219, 350});
    drawLine({901 + 45, 350}, {901 + 219 - 45, 350});
    drawLine({161 + 40 - 35, 350}, {161 - 40 + 219 - 35, 350});

    _text.setCharacterSize(24);
    _text.setString("Graphical libraries");
    _text.setPosition(640, 325);
    centerTextOrigin();
    drawTextWithColor(sf::Color::White);
    _text.setString("Games");
    _text.setPosition(1010, 325);
    centerTextOrigin();
    drawTextWithColor(sf::Color::White);
    _text.setString("Controls");
    _text.setPosition(235, 325);
    centerTextOrigin();
    drawTextWithColor(sf::Color::White);
    _text.setCharacterSize(20);

    for (size_t i = 0; i < graphics.size(); i++) {
        _text.setString(graphics[i]);
        _text.setPosition(640, 380 + i * 45);
        centerTextOrigin();
        drawTextWithColor(i == selectedGraph ? sf::Color::Red : sf::Color::White);
    }

    for (size_t i = 0; i < games.size(); i++) {
        _text.setString(games[i]);
        _text.setPosition(1010, 380 + i * 45);
        centerTextOrigin();
        drawTextWithColor(i == selectedGame ? sf::Color::Red : sf::Color::White);
    }

    for (auto &key : map)
        controls.push_back(key.first + " : " + key.second);
    for (size_t i = 0; i < controls.size(); i++) {
        _text.setString(controls[i]);
        _text.setPosition(235, 380 + i * 45);
        centerTextOrigin();
        drawTextWithColor(sf::Color::White);
    }

    _window.display();
}
