/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** GameData
*/

#ifndef CENTIPEDEGAMEDATA_HPP_
#define CENTIPEDEGAMEDATA_HPP_

#include "GameInterfaces.hpp"
#include "Entity.hpp"

namespace Arcade {
    namespace Centipede {
        class GameData : public IGameData {
            public:
                GameData();
                ~GameData();
                std::map<std::string, int> getScores() const;
                std::string getGameName() const;
                std::vector<std::shared_ptr<IEntity>> &getEntities();
                std::pair<int, int> getMapSize() const;
                const ControlMap &getControls() const override {return _controls;}
                void addScore(std::string name, int score);
                void addEntity(std::shared_ptr<IEntity> entity);
                void removeEntities();
                bool isGameOver() const;
                void setGameOver(int gameOver);
            private:
                std::map<std::string, int> _scores;
                std::vector<std::shared_ptr<IEntity>> _entities;
                ControlMap _controls;
                bool _gameOver;
        };
    }
}
#endif /* !GAMEDATA_HPP_ */
