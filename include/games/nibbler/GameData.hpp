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

namespace Arcade::Games::Nibbler {
    /**
     * @brief The Nibbler GameData.
     */
    class GameData : public IGameData {
    public:
        GameData();

        ~GameData();

        /**
         * @see IGameData::isGameOver
         */
        bool isGameOver() const override;

        /**
         * @see IGameData::getScores
         */
        std::map<std::string, int> getScores() const override;

        /**
         * @see IGameData::getGameName
         */
        std::string getGameName() const override;

        /**
         * @see IGameData::getEntities
         */
        std::vector<std::shared_ptr<IEntity>> &getEntities() override;

        /**
         * @see IGameData::getMapSize
         */
        std::pair<int, int> getMapSize() const override;

        /**
         * @see IGameData::getControls
         */
        const ControlMap &getControls() const override { return _controls; }

        /**
         * @brief Adds a score to the GameData.
         * @param name The score name
         * @param score The score value
         */
        void addScore(std::string name, int score);

        /**
         * @brief Adds an entity to the GameData.
         * @param entity The entity to add
         */
        void addEntity(std::shared_ptr<IEntity> entity);

        /**
         * @brief Removes all entities from the GameData.
         */
        void removeEntities();

        /**
         * @brief Sets the game over state.
         * @param gameOver The game over state
         */
        void setGameOver(int gameOver);

        void clearScores();

    private:
        std::map<std::string, int> _scores;
        std::vector<std::shared_ptr<IEntity>> _entities;
        ControlMap _controls;
        int _gameOver;
    };
}
#endif /* !GAMEDATA_HPP_ */
