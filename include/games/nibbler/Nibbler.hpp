/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "games/nibbler/Entity.hpp"
#include "GameInterfaces.hpp"
#include "games/nibbler/Snake.hpp"
#include "games/nibbler/GameData.hpp"
#include <memory>

namespace Arcade {
    namespace Nibbler {

        class Game : public Arcade::IGame {
            public:
                Game();
                ~Game();
                void handleKeys(const std::vector<Key> &pressedKeys);
                void update();
                IGameData &getGameData() const;
                bool exit() const;
            protected:
            private:
                std::pair<float, float> changeDirection();
                char getAtPos(int x, int y);
                char getAtPos(std::pair<int, int> pos, int x = 0, int y = 0);
                void restart();
                void initMap();
                void convertToGameData();

                std::shared_ptr<GameData> _gameData;
                char _map[19][19];
                Snake _snake;
                std::pair<float, float> _direction;
                clock_t _clock;
                bool _exit;
                float _time;
        };
    }
}
#endif /* !NIBBLER_HPP_ */
