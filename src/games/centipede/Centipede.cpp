/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Centipede
*/

#include "games/centipede/Centipede.hpp"
#include "games/centipede/GameData.hpp"
#include "games/centipede/Entity.hpp"
#include <chrono>
#include <iostream>
#include <cmath>
#include <fstream>
#include "GameUtils.hpp"

extern "C"
{
    void *createGame() {
        return new Arcade::Games::Centipede::Game();
    }

    void deleteGame(void *game) {
        delete static_cast<Arcade::Games::Centipede::Game *>(game);
    }
}

void Arcade::Games::Centipede::Game::restart()
{
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            _map[i][j] = ' ';
            if (j < 27 && rand() % 20 == 0) {
                if (j == 0)
                    _map[i][j] = '5';
                if (_map[i - 1][j - 1] == ' ')
                    _map[i][j] = '5';
            }
        }
    }
    _exit = false;
    p_pos = {12, 22};
    _direction = {0, 0};
    _clock = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    _snake.clear();
    _snake.push_back(Snake());
    b_pos = {-1, -1};
    _lauch = false;
    _time_dif = 0;
    _score = 0;
    nb_centi = 20;
    _best_score = 0;

    Arcade::Games::GameUtils::fetchBestScores(_gameData->getGameName(), _name, _best_score);
}

char Arcade::Games::Centipede::Game::getAtPos(int x, int y)
{
    if (x < 0 || x >= 25 || y < 0 || y >= 25)
        return 0;
    return _map[x][y];
}

char Arcade::Games::Centipede::Game::getAtPos(std::pair<int, int> pos, int x, int y)
{
    x += pos.first;
    y += pos.second;

    return getAtPos(x, y);
}


void Arcade::Games::Centipede::Game::handleKeys(const std::vector<Arcade::Key> &pressedKeys)
{
    _direction = {0, 0};
    for (auto &key : pressedKeys) {
        switch (key) {
            case Arcade::Key::Z:
                _direction.second -= 1;
                break;
            case Arcade::Key::S:
                _direction.second += 1;
                break;
            case Arcade::Key::Q:
                _direction.first -= 1;
                break;
            case Arcade::Key::D:
                _direction.first += 1;
                break;
            case Arcade::Key::Space:
                _lauch = true;
                break;
            case Arcade::Key::R:
                restart();
                break;
            default:
                break;
        }
    }
}

Arcade::Games::Centipede::Game::Game()
{
    _gameData = std::make_shared<Arcade::Games::Centipede::GameData>();
    restart();
}

Arcade::Games::Centipede::Game::~Game()
{
}

void Arcade::Games::Centipede::Game::removeSnake()
{
    for (size_t i = 0; i < _snake.size(); i++) {
        if (_snake[i].getBody().size() == 0)
            _snake.erase(_snake.begin() + i);
    }
    convertToGameData();
}

void Arcade::Games::Centipede::Game::moveShip(float dif)
{
    p_pos.first += _direction.first * dif * 25.0;
    p_pos.second += _direction.second * dif * 25.0;
    
    if (p_pos.first < 0)
        p_pos.first = 0;
    if (p_pos.first > 24)
        p_pos.first = 24;
    if (p_pos.second < 19)
        p_pos.second = 19;
    if (p_pos.second > 24)
        p_pos.second = 24;
}


void Arcade::Games::Centipede::Game::moveBullet(float dif)
{
    if (_lauch == true && b_pos.first <= -3) {
        b_pos = p_pos;
        _lauch = false;
    }
    if (b_pos.first >= -1) {
        b_pos.second -= dif * 30.0;
        if (b_pos.second < -3)
            b_pos = {-3, -3};
    }
}

int Arcade::Games::Centipede::Game::checkBulletMove(int before)
{
    std::pair<int, int> tmp;

    for (; before >= b_pos.second; before--) {
        tmp.first = int(round(b_pos.first));
        tmp.second = before;
        if (getAtPos(tmp.first, tmp.second) != ' ' && getAtPos(tmp.first, tmp.second) != 0) {
            _map[tmp.first][tmp.second] -= 1;
            if (_map[tmp.first][tmp.second] < '1' || _map[tmp.first][tmp.second] > '5') {
                _map[tmp.first][tmp.second] = ' ';
                _score += 1;
            }
            b_pos = {-1, -1};
            break;
        }
        for (size_t i = 0; i < _snake.size(); i++) {
            if (_snake[i].touch(tmp, _snake)) {
                _map[tmp.first][tmp.second] = '5';
                b_pos = {-1, -1};
                _score += 1;
                return 1;
            }
        }
    }
    return 0;  
}

void Arcade::Games::Centipede::Game::save_score(const std::string &username)
{
    if (_score < _best_score)
        return;

    Arcade::Games::GameUtils::saveScore(_gameData->getGameName(),
                                        username,
                                        _score);
    _best_score = _score;
}


void Arcade::Games::Centipede::Game::update(const std::string &username)
{
    float dif = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - _clock) / 1000.0;
    _clock = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    _time_dif += dif;
    int before = b_pos.second;

    if (_exit == true) {
        return convertToGameData();
    }
    moveShip(dif);
    moveBullet(dif);
    while (_time_dif > 0.1) {
        for (auto &snake : _snake) {
            snake.move(_map);
        }
        _time_dif -= 0.1;
    }
    _offset = _time_dif;
    for (size_t i = 0; i < _snake.size(); i++) {
        if (_snake[i].getBody()[_snake[i].getBody().size() - 1].second > 25) {
            _score -= _snake[i].getBody().size();
            _snake.erase(_snake.begin() + i);
            if (nb_centi > 0) {
                _snake.push_back(Snake());
                nb_centi -= 1;
            }
        }
    }
    if (_snake.size() == 0 && nb_centi == 0) {
        save_score(username);
        return restart();
    }
    if (_snake.size() == 0 && nb_centi > 0)
        _snake.push_back(Snake());
    for (size_t i = 0; i < _snake.size(); i++) {
        if (_snake[i].touch(p_pos, _snake)) {
            _exit = true;
            save_score(username);
            return removeSnake();
        }
    }
    if (checkBulletMove(before) == 1)
        return removeSnake();
    convertToGameData();
}

void Arcade::Games::Centipede::Game::convertToGameData()
{
    if (_exit == true)
        _gameData->setGameOver(true);
    else
        _gameData->setGameOver(false);
    _gameData->clearScores();
    _gameData->addScore("Score", _score);
    _gameData->addScore("Best score : " + _name + " ", _best_score);
    _gameData->removeEntities();
    std::string tmp;
    std::pair<float, float> size = {1, 1};
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 24; j++) {
            if (_map[i][j] != ' ') {
                tmp = _map[i][j];
                _gameData->addEntity(std::make_shared<Arcade::Games::Centipede::Entity>(std::vector<std::pair<float, float>>{{i, j}}, size, tmp, 0.f));
            }
        }
    }
    _gameData->addEntity(std::make_shared<Arcade::Games::Centipede::Entity>(std::vector<std::pair<float, float>>{p_pos}, size, "ship", 0.f));
    _gameData->addEntity(std::make_shared<Arcade::Games::Centipede::Entity>(std::vector<std::pair<float, float>>{b_pos}, size, "bullet", 0.f));
    std::vector<std::pair<float, float>> heads = {};
    std::vector<std::pair<float, float>> bodys = {};
    for (auto &snake : _snake) {
        std::vector<std::pair<int, int>> body = snake.getBody();
        std::pair<int, int> head = snake.getHead();
        std::pair<float, float> pos = {(head.first - body[0].first) * _offset * 10 / 1.0, (head.second - body[0].second) * _offset * 10 / 1.0};
        heads.push_back({body[0].first + pos.first, body[0].second + pos.second});
        for (size_t i = 1; i < body.size(); i++) {
            pos = {(body[i - 1].first - body[i].first) * _offset * 10 / 1.0, (body[i - 1].second - body[i].second) * _offset * 10 / 1.0};
            bodys.push_back({body[i].first + pos.first, body[i].second + pos.second});
        }
    }
    _gameData->addEntity(std::make_shared<Arcade::Games::Centipede::Entity>(bodys, size, "body", 0.f));
    _gameData->addEntity(std::make_shared<Arcade::Games::Centipede::Entity>(heads, size, "head", 0.f));
    // _gameData->addScore("Score", _body.size() - 4);
}


Arcade::IGameData &Arcade::Games::Centipede::Game::getGameData() const
{
    return *_gameData;
}
