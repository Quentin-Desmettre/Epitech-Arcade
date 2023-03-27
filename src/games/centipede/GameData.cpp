/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** GameData
*/

#include "games/centipede/GameData.hpp"
#include "games/centipede/Centipede.hpp"
#include <iostream>

Arcade::Centipede::GameData::GameData()
{
    _scores = {};
    _scores["Score"] = 0;
    _entities = {};
}

Arcade::Centipede::GameData::~GameData()
{
}

std::map<std::string, int> Arcade::Centipede::GameData::getScores() const
{
    return _scores;
}

std::string Arcade::Centipede::GameData::getGameName() const
{
    return "Centipede";
}

std::vector<std::shared_ptr<Arcade::IEntity>> &Arcade::Centipede::GameData::getEntities()
{
    return _entities;
}

std::pair<int, int> Arcade::Centipede::GameData::getMapSize() const
{
    return {25, 25};
}

void Arcade::Centipede::GameData::addScore(std::string name, int score)
{
    _scores[name] = score;
}

void Arcade::Centipede::GameData::addEntity(std::shared_ptr<Arcade::IEntity> entity)
{
    _entities.push_back(entity);
}

void Arcade::Centipede::GameData::removeEntities()
{
    _entities.clear();
}

void Arcade::Centipede::GameData::setGameOver(int gameOver)
{
    _gameOver = gameOver;
}

bool Arcade::Centipede::GameData::isGameOver() const
{
    return _gameOver;
}