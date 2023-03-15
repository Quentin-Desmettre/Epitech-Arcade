/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Snake
*/

#include "games/nibbler/Snake.hpp"
#include <cmath>

void Arcade::Nibbler::Snake::move(float dif, std::pair<float, float> dir)
{
    float length = 0;
    std::pair<float, float> pos = getFuturHead(dir);
    std::pair<float, float> newPos = _snake[0].getPosition();
    std::pair<float, float> oldPos;
    std::pair<float, float> norm_vec;
    for (std::size_t i = 1; i < _snake.size(); i++) {
        oldPos = _snake[i].getPosition();
        length = sqrt(pow(newPos.first - oldPos.first, 2) + pow(newPos.second - oldPos.second, 2));
        norm_vec = {(newPos.first - oldPos.first) / length, (newPos.second - oldPos.second) / length};
        newPos = {oldPos.first + norm_vec.first * dif * 10, oldPos.second + norm_vec.second * dif * 10};
        _snake[i].setPosition(newPos);
        _snake[i].setRotation(atan2(norm_vec.first, norm_vec.second));
        newPos = _snake[i].getPosition();
    }
    _snake[0].setPosition(pos);
}

void Arcade::Nibbler::Snake::born()
{
    _snake.clear();
    _snake.push_back(Arcade::Nibbler::Entity({19 / 2 + 2, 18}, {1, 1}, "snake_head", 0));
    _snake.push_back(Arcade::Nibbler::Entity({19 / 2 + 1, 18}, {1, 1}, "snake_body", 0));
    _snake.push_back(Arcade::Nibbler::Entity({19 / 2, 18}, {1, 1}, "snake_body", 0));
    _snake.push_back(Arcade::Nibbler::Entity({19 / 2 - 1, 18}, {1, 1}, "snake_tail", 0));
}

Arcade::Nibbler::Snake::Snake()
{
    born();
}

Arcade::Nibbler::Snake::~Snake()
{
    _snake.clear();
}

bool Arcade::Nibbler::Snake::isDead()
{
    for (std::size_t i = 3; i < _snake.size(); i++) {
        if (_snake[0].isColliding(_snake[i])) {
            return true;
        }
    }
    return false;
}

void Arcade::Nibbler::Snake::deleleteImpossibleDir(std::vector<std::pair<int, int>> &dir) const
{
    std::pair<float, float> head = _snake[0].getPosition();
    std::pair<float, float> body = _snake[1].getPosition();
    float length = sqrt(pow(head.first - body.first, 2) + pow(head.second - body.second, 2));
    std::pair<float, float> norm_vec = {(head.first - body.first) / length, (head.second - body.second) / length};
    int diff[dir.size()];
    if (dir.size() == 1)
        return;
    for (std::size_t i = 0; i < dir.size(); i++)
        diff[i] = abs(atan2(dir[i].first, dir[i].second) - atan2(norm_vec.first, norm_vec.second));
    int min = diff[0];
    int index = 0;
    for (std::size_t i = 1; i < dir.size(); i++) {
        if (diff[i] < min) {
            min = diff[i];
            index = i;
        }
    }
    dir.erase(dir.begin() + index);
}

std::pair<float, float> Arcade::Nibbler::Snake::getFuturHead(std::pair<float, float> direction) const
{
    return {_snake[0].getPosition().first + direction.first, _snake[0].getPosition().second + direction.second};
}

std::vector<Arcade::Nibbler::Entity> &Arcade::Nibbler::Snake::getSnake()
{
    return _snake;
}