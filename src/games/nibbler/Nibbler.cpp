/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Nibbler
*/
#include "games/nibbler/Nibbler.hpp"
#include "games/nibbler/GameData.hpp"
#include "games/nibbler/Entity.hpp"
#include <iostream>
#include <string>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <cmath>
#include <memory>

void Arcade::Nibbler::Game::initMap()
{
    std::string mapString = 
    "XXXXXXXXXXXXXXXXXXX"
    "X                 X"
    "X XXX X XXX X XXX X"
    "X X/X X     X X/X X"
    "X XXX X X X X XXX X"
    "X     X X X X     X"
    "X XXXXX X X XXXXX X"
    "X X             X X"
    "X X XXXXX XXXXX X X"
    "X                 X"
    "X XXXXX XXX XXXXX X"
    "X       X/X       X"
    "X XXX X XXX X XXX X"
    "X X/X X     X X/X X"
    "X XXX X XXX X XXX X"
    "X     X X/X X     X"
    "X XXXXX XXX XXXXX X"
    "X                 X"
    "XXXXXXXXXXXXXXXXXXX";
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (mapString[i * 19 + j] == ' ' && rand() % 10 == 0)
                _map[i][j] = 'o';
            else
                _map[i][j] = mapString[i * 19 + j];
        }
    }
}

void Arcade::Nibbler::Game::restart()
{
    initMap();
    _gameData->addScore("Score", 0);
    _gameData->addScore("Time", 990);
    _time = _gameData->getScores()["Time"];
    _direction = {0, 1};
    _clock = clock();
    
}

Arcade::Nibbler::Game::Game()
{
    srand(time(NULL));
    
    _exit = false;
    _gameData = std::make_shared<Arcade::Nibbler::GameData>();
    restart();
}

Arcade::Nibbler::Game::~Game()
{
}


void Arcade::Nibbler::Game::handleKeys(const std::vector<Arcade::Key> &pressedKeys)
{
    for (auto &key : pressedKeys) {
        switch (key) {
            case Arcade::Key::Up:
                _direction = {-1, 0};
                break;
            case Arcade::Key::Down:
                _direction = {1, 0};
                break;
            case Arcade::Key::Left:
                _direction = {0, -1};
                break;
            case Arcade::Key::Right:    
                _direction = {0, 1};
                break;
            case Arcade::Key::Escape:
                _exit = true;
                break;
            default:
                _direction = {0, 0};
                break;
        }
    }
}

char Arcade::Nibbler::Game::getAtPos(int x, int y)
{
    if (x < 0 || x >= 19 || y < 0 || y >= 19)
        return 'X';
    return _map[x][y];
}

char Arcade::Nibbler::Game::getAtPos(std::pair<int, int> pos, int x, int y)
{
    x += pos.first;
    y += pos.second;

    return getAtPos(x, y);
}

std::pair<float, float> Arcade::Nibbler::Game::changeDirection()
{
    std::pair<int, int> pos = _snake.getSnake()[0].getPosition();
    std::vector<std::pair<int, int>> dir = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    for (int i = 0; i < 4; i++) {
        if (getAtPos(pos, dir[i].first, dir[i].second) == 'X')
            dir.erase(dir.begin() + i);
    }
    _snake.deleteImpossibleDir(dir);
    if (dir.size() == 0)
        std::cout << "ERROR stuck" << std::endl;
    if (dir.size() == 1)
        return dir[0];
    for (size_t i = 0; i < dir.size(); i++) {
        if (dir[i].first == _direction.first && dir[i].second == _direction.second)
            return dir[i];
    }
    return {0, 0};
}

void Arcade::Nibbler::Game::update()
{
    float dif = (clock() - _clock) / (float) CLOCKS_PER_SEC;
    _clock = clock();

    _time -= dif;
    if (_time < 0) {
        _time = 0;
        return;
    }
    std::pair<float, float> dir = changeDirection();
    dir.first *= dif * 10;
    dir.second *= dif * 10;
    _snake.move(dif, dir);
    // if (_snake.isDead())
    //     restart();
    convertToGameData();
}

void Arcade::Nibbler::Game::convertToGameData()
{
    _gameData->getEntities().clear();
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (_map[i][j] == 'X') {
                _gameData->addEntity(new Arcade::Nibbler::Entity({i, j}, {1, 1}, "fruit", 0));
                // std::cout << _gameData->getEntities().size() << std::endl;
            }
            if (_map[i][j] == 'o') {
                _gameData->addEntity(new Arcade::Nibbler::Entity({i, j}, {1, 1}, "fruit", 0));
                // std::cout << _gameData->getEntities().size() << std::endl;
            }
        }
    }

    // for (auto &entity : _snake.getSnake()) {
    //     _gameData->addEntity(entity);
    // }
    // std::cout << _gameData->getEntities().size() << std::endl;
    // for (auto &entity : _gameData->getEntities()) {
    //     std::cout << entity.getTexture() << std::endl;
    // }
    _gameData->addScore("Score", 0);
    _gameData->addScore("Time", _time);
}

Arcade::IGameData &Arcade::Nibbler::Game::getGameData() const
{
    return *_gameData;
}

bool Arcade::Nibbler::Game::exit() const
{
    return _exit;
}