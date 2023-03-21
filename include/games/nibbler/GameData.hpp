/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** GameData
*/

#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <memory>
#include "GameInterfaces.hpp"
#include "Entity.hpp"

namespace Arcade {
    namespace Nibbler {
        class GameData : public IGameData {
            public:
                GameData();
                ~GameData();
                bool isGameOver() const override;
                std::map<std::string, int> getScores() const;
                std::string getGameName() const;
                std::vector<std::shared_ptr<IEntity>> &getEntities();
                std::pair<int, int> getMapSize() const;
                const ControlMap &getControls() const override {return _controls;}
                void addScore(std::string name, int score);
                void addEntity(std::shared_ptr<IEntity> entity);
                void removeEntities();
            private:
                std::map<std::string, int> _scores;
                std::vector<std::shared_ptr<IEntity>> _entities;
                ControlMap _controls;
        };
    }
}
#endif /* !GAMEDATA_HPP_ */
