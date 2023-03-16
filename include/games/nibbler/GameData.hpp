/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** GameData
*/

#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include "GameInterfaces.hpp"
#include "Entity.hpp"

namespace Arcade {
    namespace Nibbler {
        class GameData : public IGameData {
            public:
                GameData();
                ~GameData();
                std::map<std::string, int> getScores() const;
                std::string getGameName() const;
                std::vector<IEntity *> &getEntities();
                std::pair<int, int> getMapSize() const;   
                void addScore(std::string name, int score);             
                void addEntity(IEntity *entity);
            private:
                std::map<std::string, int> _scores;
                std::vector<IEntity *> _entities;
        };
    }
}
#endif /* !GAMEDATA_HPP_ */
