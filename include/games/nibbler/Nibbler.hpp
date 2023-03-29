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
#include "games/nibbler/GameData.hpp"
#include <memory>

namespace Arcade {
    namespace Nibbler {

        class Game : public Arcade::IGame {
            public:
                Game();
                ~Game() override;
                void handleKeys(const std::vector<Key> &pressedKeys) override;
                void update(const std::string &username) override;
                IGameData &getGameData() const override;
            protected:
            private:
                std::pair<float, float> changeDirection();
                char getAtPos(int x, int y);
                char getAtPos(std::pair<int, int> pos, int x = 0, int y = 0);
                void restart();
                void initMap();
                void convertToGameData();
                void folowSnake(std::pair<int, int> pos);
                void growUpSnake();
                void save_score(const std::string &username);
                int isSnakeDead();

                std::shared_ptr<GameData> _gameData;
                char _map[19][19];
                std::pair<int, int> _head;
                std::vector<std::pair<int, int>> _body;
                std::pair<float, float> _direction;
                std::pair<int, int> _child;
                bool _is_child;
                long _clock;
                bool _exit;
                float _time;
                float _time_dif;
                float _offset;
                bool _is_stuck;
                int _best_score;
                std::string _name;
        };
    }
}
#endif /* !NIBBLER_HPP_ */
