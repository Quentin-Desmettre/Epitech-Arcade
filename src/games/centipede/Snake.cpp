/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Snake
*/

#include "games/centipede/Snake.hpp"
#include <iostream>

Arcade::Games::Centipede::Snake::Snake()
{
    _head = {12, 0};
    for (int i = 0; i < 8; i++) {
        _body.push_back({12, -1});
    }
    _tail = {10, 0};
    _dir = true;
}

Arcade::Games::Centipede::Snake::Snake(std::pair<int, int> head, std::pair<int, int> tail, std::vector<std::pair<int, int>> body, bool dir)
{
    _head = head;
    _tail = tail;
    _body = body;
    _dir = dir;
}

Arcade::Games::Centipede::Snake::~Snake()
{
}

void Arcade::Games::Centipede::Snake::folow(std::pair<int, int> pos)
{
    _tail = _body.back();
    for (size_t i = _body.size() - 1; i > 0; i--) {
        _body[i] = _body[i - 1];
    }
    _body[0] = _head;
    _head = pos;
}

void Arcade::Games::Centipede::Snake::move(char map[25][25])
{
    int x = _head.first + (_dir ? 1 : -1);
    int y = _head.second;
    if (x < 0 || x >= 25 || y < 0 || y >= 25) {
        _dir = !_dir;
        return folow({_head.first, _head.second + 1});
    }
    if (map[x][y] == ' ') {
        return folow({x, y});
    }
    _dir = !_dir;
    return folow({_head.first, _head.second + 1});
}

int Arcade::Games::Centipede::Snake::touch(std::pair<int, int> pos, std::vector<Arcade::Games::Centipede::Snake> &snakes)
{
    std::vector<std::pair<int, int>> tmp = {};
    size_t size = _body.size();
    if (_body[size - 1] == pos) {
        _tail = _body[size - 1];
        _body.pop_back();
        return 1;
    }
    for (size_t i = 0; i < size; i++) {
        if (_body[i] == pos) {
            for (size_t j = i + 1; j < size; j++)
                tmp.push_back(_body[j]);
            for (size_t j = i; j < size; j++)
                _body.pop_back();
            snakes.push_back(Snake(_body[i + 1], _tail, tmp, _dir));
            return 1;
        }
    }
    return 0;
}

std::vector<std::pair<int, int>> Arcade::Games::Centipede::Snake::getBody() const
{
    return _body;
}

std::pair<int, int> Arcade::Games::Centipede::Snake::getHead() const
{
    return _head;
}