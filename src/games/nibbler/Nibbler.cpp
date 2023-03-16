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
#include <cmath>
#include <memory>
#include <chrono>

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
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
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
    _direction = {1, 0};
    _body.clear();

    _clock = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    _exit = false;
    _head = {19 / 2 + 2, 17};
    for (int i = 0; i < 4; i++)
        _body.push_back({19 / 2 + 1 - i, 17});
    _time_dif = 0;
    _is_stuck = false;
}

Arcade::Nibbler::Game::Game()
{
    srand(time(NULL));

    _gameData = std::make_shared<Arcade::Nibbler::GameData>();
    _body = {};
    restart();
}

Arcade::Nibbler::Game::~Game()
{
}

void Arcade::Nibbler::Game::handleKeys(const std::vector<Arcade::Key> &pressedKeys)
{
    for (auto &key : pressedKeys)
    {
        switch (key) {
        case Arcade::Key::Up:
            _direction = {0, -1};
            break;
        case Arcade::Key::Down:
            _direction = {0, 1};
            break;
        case Arcade::Key::Left:
            _direction = {-1, 0};
            break;
        case Arcade::Key::Right:
            _direction = {1, 0};
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

void Arcade::Nibbler::Game::folowSnake(std::pair<int, int> pos)
{
    for (size_t i = _body.size() - 1; i > 0; i--) {
        _body[i] = _body[i - 1];
    }
    _body[0] = _head;
    _head.first += pos.first;
    _head.second += pos.second;
}

std::pair<float, float> Arcade::Nibbler::Game::changeDirection()
{
    std::vector<std::pair<int, int>> dir = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    std::pair<int, int> def = {_head.first * 2 - _body[0].first, _head.second * 2 - _body[0].second}; 
    for (size_t i = 0; i < dir.size(); i++) {
        if (getAtPos(_head, dir[i].first, dir[i].second) == 'X' || (_head.first + dir[i].first == _body[0].first && _head.second + dir[i].second == _body[0].second)) {
            dir.erase(dir.begin() + i);
            i--;
        }
    }
    if (dir.size() == 0)
        std::cout << "ERROR stuck" << std::endl;
    if (dir.size() == 1) {
        folowSnake(dir[0]);
        return dir[0];
    }
    for (size_t i = 0; i < dir.size(); i++) {
        if (dir[i].first == _direction.first && dir[i].second == _direction.second) {
            folowSnake(dir[i]);
            return dir[i];
        }
    }
    if (getAtPos(def) != 'X') {
        folowSnake({def.first - _body[0].first, def.second - _body[0].second});
        return {def.first - _body[0].first, def.second - _body[0].second};
    }
    return {0, 0};
}

void Arcade::Nibbler::Game::update()
{
    float dif = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - _clock) / 1000.0;
    _clock = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    _time_dif += dif;

    _time -= dif;
    if (_time < 0) {
        _time = 0;
        return;
    }
    if (_time_dif > 0.5 || _is_stuck == true) {
        if (_is_stuck == true)
            _time_dif = 0.5;
        std::pair<float, float> dir = changeDirection();
        if (dir.first == 0 && dir.second == 0)
            _is_stuck = true;
        else
            _is_stuck = false;
        _direction = dir;
        _time_dif -= 0.5;
    }
    if (_is_stuck == false)
        _offset = _time_dif;
    else
        _offset = 0.5;
    convertToGameData();
}

void Arcade::Nibbler::Game::convertToGameData()
{
    _gameData->getEntities().clear();
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (_map[i][j] == 'X')
                _gameData->addEntity(new Arcade::Nibbler::Entity({i, j}, {1, 1}, "wall", 0));
            if (_map[i][j] == 'o')
                _gameData->addEntity(new Arcade::Nibbler::Entity({i, j}, {1, 1}, "fruit", 0));
        }
    }
    std::pair<float, float> pos = {(_head.first - _body[0].first) * _offset * 2, (_head.second - _body[0].second) * _offset * 2};
    _gameData->addEntity(new Arcade::Nibbler::Entity({_body[0].first + pos.first, _body[0].second + pos.second}, {1, 1}, "fruit", 0));
    for (size_t i = 1; i < _body.size(); i++) {
        pos = {(_body[i - 1].first - _body[i].first) * _offset * 2, (_body[i - 1].second - _body[i].second) * _offset * 2};
        _gameData->addEntity(new Arcade::Nibbler::Entity({_body[i].first + pos.first, _body[i].second + pos.second}, {1, 1}, "fruit", 0));
    }
    _gameData->addScore("Score", 0);
    _gameData->addScore("Time", _time);
}

Arcade::IGameData &Arcade::Nibbler::Game::getGameData() const
{
    return *_gameData;
}
