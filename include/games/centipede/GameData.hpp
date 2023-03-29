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

namespace Arcade::Games::Centipede {
    /**
     * @brief The Centipede GameData.
     */
    class GameData : public IGameData {
    public:
        /**
         * @brief Creates a new GameData.
         */
        GameData();

        ~GameData();

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
         * @see IGameData::isGameOver
         */
        bool isGameOver() const override;

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
         * @brief Adds an Entity to the GameData.
         * @param entity The Entity to add.
         */
        void addEntity(std::shared_ptr<IEntity> entity);

        /**
         * @brief Removes all the Entities from the GameData.
         */
        void removeEntities();

        /**
         * @brief Sets the GameData as over.
         * @param gameOver The new value of the gameover.
         */
        void setGameOver(int gameOver);

        void clearScores();

    private:
        std::map<std::string, int> _scores;
        std::vector<std::shared_ptr<IEntity>> _entities;
        ControlMap _controls;
        bool _gameOver;
    };
}

#endif /* !GAMEDATA_HPP_ */
