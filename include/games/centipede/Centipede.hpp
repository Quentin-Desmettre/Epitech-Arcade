/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Centipede
*/

#ifndef Centipede_HPP_
#define Centipede_HPP_

#include "games/centipede/Entity.hpp"
#include "GameInterfaces.hpp"
#include "games/centipede/GameData.hpp"
#include "games/centipede/Snake.hpp"
#include <memory>

/**
 * @brief The Centipede game library namespace.
 */
namespace Arcade::Games::Centipede {
    /**
     * @brief The Centipede game class.
     */
    class Game : public Arcade::IGame {
        public:
            /**
             * @brief Creates a new Centipede game.
             */
            Game();
            ~Game() override;

            /**
             * @see IGame::handleKeys
             */
            void handleKeys(const std::vector<Key> &pressedKeys) override;

            /**
             * @see IGame::update
             */
            void update(const std::string &username) override;

            /**
             * @see IGame::getGameData
             */
            IGameData &getGameData() const override;
        protected:
        private:
            char getAtPos(int x, int y);
            char getAtPos(std::pair<int, int> pos, int x = 0, int y = 0);
            void restart();
            void convertToGameData();
            void removeSnake();
            void moveShip(float dif);
            void moveBullet(float dif);
            int checkBulletMove(int before);
            void save_score(const std::string &username);

            std::shared_ptr<Centipede::GameData> _gameData;
            char _map[25][25];
            std::vector<Centipede::Snake> _snake;
            long _clock;
            std::pair<int, int> _direction;
            std::pair<float, float> p_pos;
            std::pair<float, float> b_pos;
            bool _exit;
            bool _lauch;
            float _time;
            float _time_dif;
            float _offset;
            int _best_score;
            std::string _name;
            int _score;
            int nb_centi;
    };
}
#endif /* !centipede_HPP_ */
