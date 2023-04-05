/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** GameData
*/

#include "games/centipede/GameData.hpp"
#include "games/centipede/Centipede.hpp"
#include <iostream>

Arcade::Games::Centipede::GameData::GameData()
{
    _scores = {};
    _scores["Score"] = 0;
    _entities = {};
    _controls = {
            {"Up",                "Z"},
            {"Down",              "S"},
            {"Left",              "Q"},
            {"Right",             "D"},
            {"Shoot",             "SPACE"},
            {"Restart",           "R"},
    };
}

Arcade::Games::Centipede::GameData::~GameData()
{
}

std::map<std::string, int> Arcade::Games::Centipede::GameData::getScores() const
{
    return _scores;
}

void Arcade::Games::Centipede::GameData::clearScores()
{
    _scores.clear();
}

std::string Arcade::Games::Centipede::GameData::getGameName() const
{
    return "Centipede";
}

std::vector<std::shared_ptr<Arcade::IEntity>> &Arcade::Games::Centipede::GameData::getEntities()
{
    return _entities;
}

std::pair<int, int> Arcade::Games::Centipede::GameData::getMapSize() const
{
    return {25, 25};
}

void Arcade::Games::Centipede::GameData::addScore(std::string name, int score)
{
    _scores[name] = score;
}

void Arcade::Games::Centipede::GameData::addEntity(std::shared_ptr<Arcade::IEntity> entity)
{
    _entities.push_back(entity);
}

void Arcade::Games::Centipede::GameData::removeEntities()
{
    _entities.clear();
}

void Arcade::Games::Centipede::GameData::setGameOver(int gameOver)
{
    _gameOver = gameOver;
}

bool Arcade::Games::Centipede::GameData::isGameOver() const
{
    return _gameOver;
}