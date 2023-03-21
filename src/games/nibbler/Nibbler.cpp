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
            if (mapString[i * 19 + j] == ' ' && rand() % 5 == 0)
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
    _gameData->addScore("Time", 60);
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
    _is_child = false;
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
        case Arcade::Key::Z:
            _direction = {0, -1};
            break;
        case Arcade::Key::S:
            _direction = {0, 1};
            break;
        case Arcade::Key::Q:
            _direction = {-1, 0};
            break;
        case Arcade::Key::D:
            _direction = {1, 0};
            break;
        case Arcade::Key::Space:
            restart();
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

void Arcade::Nibbler::Game::growUpSnake()
{
    if (_is_child) {
        _body.push_back(_child);
        _is_child = false;
    }
    if (getAtPos(_body[0].first, _body[0].second) == 'o') {
        _map[_body[0].first][_body[0].second] = ' ';
        _is_child = true;
        _child = _body.back();
    }
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
    std::pair<int, int> dif = {def.first - _head.first, def.second - _head.second};
    for (size_t i = 0; i < dir.size(); i++) {
        if (getAtPos(_head, dir[i].first, dir[i].second) == 'X' || (_head.first + dir[i].first == _body[0].first && _head.second + dir[i].second == _body[0].second)) {
            dir.erase(dir.begin() + i);
            i--;
        }
    }
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
        folowSnake(dif);
        return dif;
    }
    return {0, 0};
}

int Arcade::Nibbler::Game::isSnakeDead()
{
    for (size_t i = 1; i < _body.size(); i++) {
        if (_is_stuck && _head.first == _body[i].first && _head.second == _body[i].second) {
            _exit = true;
            return 1;
        }
        if (_body[0].first == _body[i].first && _body[0].second == _body[i].second) {
            _exit = true;
            return 1;
        }
    }
    return 0;
}

void Arcade::Nibbler::Game::update(const std::string &username)
{
    float dif = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - _clock) / 1000.0;
    _clock = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    _time_dif += dif;

    _time -= dif;
    _time = _time < 0 ? 0 : _time;
    if (_time == 0 || _exit == true) {
        return;
    }
    while (_time_dif > 0.4 || _is_stuck == true) {
        if (_is_stuck == true)
            _time_dif = 0.4;
        std::pair<float, float> dir = changeDirection();
        if (dir.first == 0 && dir.second == 0)
            _is_stuck = true;
        else {
            _is_stuck = false;
            growUpSnake();
        }
        if (isSnakeDead())
            return;
        _direction = dir;
        _time_dif -= 0.4;
        if (_is_stuck == true)
            break;
    }
    if (_is_stuck == false)
        _offset = _time_dif;
    else
        _offset = 0.4;
    convertToGameData();
}

void Arcade::Nibbler::Game::convertToGameData()
{
    _gameData->removeEntities();
    std::pair<float, float> size = {1, 1};
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (_map[i][j] == 'X') {
                _gameData->addEntity(std::make_shared<Arcade::Nibbler::Entity>(std::pair<float, float>({i, j}), size, "wall", 0.f));
            }

            if (_map[i][j] == 'o')
                _gameData->addEntity(std::make_shared<Arcade::Nibbler::Entity>(std::pair<float, float>{i, j}, size, "fruit", 0.f));
        }
    }
    if (_is_child)
        _gameData->addEntity(std::make_shared<Arcade::Nibbler::Entity>(std::pair<float, float>{_child.first, _child.second}, size, "body", 0));
    std::pair<float, float> pos = {(_head.first - _body[0].first) * _offset * 10 / 4.0, (_head.second - _body[0].second) * _offset * 10 / 4.0};
    _gameData->addEntity(std::make_shared<Arcade::Nibbler::Entity>(std::pair<float, float>{_body[0].first + pos.first, _body[0].second + pos.second}, size, std::string("head"), 0.f));
    for (size_t i = 1; i < _body.size(); i++) {
        pos = {(_body[i - 1].first - _body[i].first) * _offset * 10 / 4.0, (_body[i - 1].second - _body[i].second) * _offset * 10 / 4.0};
        _gameData->addEntity(std::make_shared<Arcade::Nibbler::Entity>(std::pair<float, float>{_body[i].first + pos.first, _body[i].second + pos.second}, size, std::string("body"), 0.f));
    }
    _gameData->addScore("Score", _body.size() - 4);
    _gameData->addScore("Time", _time);
}

Arcade::IGameData &Arcade::Nibbler::Game::getGameData() const
{
    return *_gameData;
}
