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
    _isMenu = true;
}

Arcade::SFML::~SFML()
{
    _window.close();
}

std::vector<Arcade::Key> Arcade::SFML::getPressedKeys()
{
    std::vector<Arcade::Key> keys;

    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            keys.push_back(Arcade::Key::Escape);
            if (_isMenu)
                _window.close();
        }
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
                case sf::Keyboard::Z:
                    keys.push_back(Arcade::Key::Z);
                    break;
                case sf::Keyboard::Q:
                    keys.push_back(Arcade::Key::Q);
                    break;
                case sf::Keyboard::S:
                    keys.push_back(Arcade::Key::S);
                    break;
                case sf::Keyboard::D:
                    keys.push_back(Arcade::Key::D);
                    break;
                case sf::Keyboard::R:
                    keys.push_back(Arcade::Key::R);
                    break;
                default:
                    break;
            }
        }
    }
    return keys;
}

void Arcade::SFML::drawInfoPanel(Arcade::IGameData &gameData)
{
    _text.setCharacterSize(30);
    _text.setString(gameData.getGameName());
    _text.setPosition(((0.3 + gameData.getMapSize().second) * _cellSize + 1280) / 2, 25);
    centerTextOrigin();
    _window.draw(_text);
    _text.setCharacterSize(24);

    for (int i = 0; auto &score : gameData.getScores()) {
        _text.setString(score.first + ": " + std::to_string(score.second));
        _text.setPosition((0.3 + gameData.getMapSize().second) * _cellSize + 90, 100  + i * 50);
        _window.draw(_text);
        i++;
    }

    if (gameData.isGameOver()) {
        _text.setCharacterSize(40);
        _text.setString("GAME OVER");
        _text.setFillColor(sf::Color::Red);
        _text.setPosition(((0.25 + gameData.getMapSize().second) * _cellSize + 1280) / 2, 700);
        centerTextOrigin();
        _window.draw(_text);
        _text.setFillColor(sf::Color::White);
    }
}

void Arcade::SFML::render(Arcade::IGameData &gameData)
{
    std::vector<std::shared_ptr<IEntity>> entities = gameData.getEntities();
    std::vector<std::pair<float, float>> positon;

    _isMenu = false;
    _window.clear();
    calculateCellSize(gameData.getMapSize().first, gameData.getMapSize().second);
    for (auto &entity : entities) {
        if (loadTexture("assets/" + gameData.getGameName() + "/sfml/" + entity->getTexture()) == false)
            continue;
        _sprite.setTexture(*_textureMap["assets/" + gameData.getGameName() + "/sfml/" + entity->getTexture()].get());
        _sprite.setTextureRect(sf::IntRect(0, 0, _sprite.getTexture()->getSize().x, _sprite.getTexture()->getSize().y));
        _sprite.setScale(1, 1);
        _sprite.scale(_cellSize / _sprite.getLocalBounds().width * entity->getSize().first,
        _cellSize / _sprite.getLocalBounds().height * entity->getSize().second);
        _sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
        _sprite.setRotation(entity->getRotation());
        positon = entity->getPosition();
        for (auto &pos : positon) {
            _sprite.setPosition((0.5 + pos.first) * _cellSize, (0.5 + pos.second) * _cellSize);
            _window.draw(_sprite);
        }
    }
    drawInfoPanel(gameData);
    _window.display();
}

std::string Arcade::SFML::truncString(std::string str)
{
    if (str.size() > 19)
        str = str.substr(0, 19) + "...";
    return str;
}

void Arcade::SFML::setupMenu()
{
    if (loadTexture("assets/menubg.png") == false)
        return;
    _sprite.setTexture(*_textureMap["assets/menubg.png"].get());
    _sprite.setTextureRect(sf::IntRect(0, 0, _sprite.getTexture()->getSize().x, _sprite.getTexture()->getSize().y));
    _sprite.setPosition(0, 0);
    _sprite.setOrigin(0, 0);
    _sprite.setScale(1, 1);
    _sprite.setRotation(0);
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
}

void Arcade::SFML::renderMenu(const std::vector<std::string> &games,
const std::vector<std::string> &graphics, int selectedGame, int selectedGraph, const ControlMap &map)
{
    std::vector<std::string> controls;

    _isMenu = true;
    _window.clear();
    setupMenu();

    for (size_t i = 0; i < graphics.size(); i++) {
        _text.setString(truncString(graphics[i]));
        _text.setPosition(640, 380 + i * 45);
        centerTextOrigin();
        drawTextWithColor(static_cast<int>(i) == selectedGraph ? sf::Color::Red : sf::Color::White);
    }
    for (size_t i = 0; i < games.size(); i++) {
        _text.setString(truncString(games[i]));
        _text.setPosition(1010, 380 + i * 45);
        centerTextOrigin();
        drawTextWithColor(static_cast<int>(i) == selectedGame ? sf::Color::Red : sf::Color::White);
    }
    for (auto &key : map)
        controls.push_back(key.first + " : " + key.second);
    for (size_t i = 0; i < controls.size(); i++) {
        _text.setString(truncString(controls[i]));
        _text.setPosition(235, 380 + i * 45);
        centerTextOrigin();
        drawTextWithColor(sf::Color::White);
    }

    _window.display();
}
