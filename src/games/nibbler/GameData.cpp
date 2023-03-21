/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** GameData
*/

#include "games/nibbler/GameData.hpp"
#include "games/nibbler/Nibbler.hpp"
#include <iostream>

Arcade::Nibbler::GameData::GameData()
{
    _scores = {};
    _scores["Time"] = 990;
    _scores["Score"] = 0;
    _entities = {};
}

Arcade::Nibbler::GameData::~GameData()
{
}

std::map<std::string, int> Arcade::Nibbler::GameData::getScores() const
{
    return _scores;
}

std::string Arcade::Nibbler::GameData::getGameName() const
{
    return "Nibbler";
}

std::vector<Arcade::IEntity *> &Arcade::Nibbler::GameData::getEntities()
{
    return _entities;
}

std::pair<int, int> Arcade::Nibbler::GameData::getMapSize() const
{
    return {19, 19};
}

void Arcade::Nibbler::GameData::addScore(std::string name, int score)
{
    _scores[name] = score;
}

void Arcade::Nibbler::GameData::addEntity(Arcade::IEntity *entity)
{
    _entities.push_back(entity);
}

void Arcade::Nibbler::GameData::removeEntities()
{
    _entities.clear();
}

bool Arcade::Nibbler::GameData::isGameOver() const
{
    return true;
}
