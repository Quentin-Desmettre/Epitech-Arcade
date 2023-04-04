/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** GameData
*/

#include "games/nibbler/GameData.hpp"
#include <iostream>

Arcade::Games::Nibbler::GameData::GameData()
{
    _scores = {};
    _scores["Time"] = 990;
    _scores["Score"] = 0;
    _entities = {};
    _controls = {
            {"Up", "Z"},
            {"Down", "S"},
            {"Left", "Q"},
            {"Right", "D"},
            {"Restart", "R"}
    };
}

Arcade::Games::Nibbler::GameData::~GameData()
{
}

std::map<std::string, int> Arcade::Games::Nibbler::GameData::getScores() const
{
    return _scores;
}

void Arcade::Games::Nibbler::GameData::clearScores()
{
    _scores.clear();
}

std::string Arcade::Games::Nibbler::GameData::getGameName() const
{
    return "Nibbler";
}

std::vector<std::shared_ptr<Arcade::IEntity>> &Arcade::Games::Nibbler::GameData::getEntities()
{
    return _entities;
}

std::pair<int, int> Arcade::Games::Nibbler::GameData::getMapSize() const
{
    return {19, 19};
}

void Arcade::Games::Nibbler::GameData::addScore(std::string name, int score)
{
    _scores[name] = score;
}

void Arcade::Games::Nibbler::GameData::addEntity(std::shared_ptr<Arcade::IEntity> entity)
{
    _entities.push_back(entity);
}

void Arcade::Games::Nibbler::GameData::removeEntities()
{
    _entities.clear();
}

bool Arcade::Games::Nibbler::GameData::isGameOver() const
{
    return _gameOver;
}

void Arcade::Games::Nibbler::GameData::setGameOver(int gameOver)
{
    _gameOver = gameOver;
}
