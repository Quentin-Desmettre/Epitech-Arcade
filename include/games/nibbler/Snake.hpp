/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "GameInterfaces.hpp"
#include "games/nibbler/Entity.hpp"

namespace Arcade {
    namespace Nibbler {
        class Snake {
            public:
                Snake();
                ~Snake();
                void move(float dif, std::pair<float, float> dir);
                void grow();
                void born();
                bool isDead();
                std::vector<Entity> &getSnake();
                void deleleteImpossibleDir(std::vector<std::pair<int, int>> &dir) const;
                std::pair<float, float> getFuturHead(std::pair<float, float> direction) const;


            private:
                std::vector<Entity> _snake;
        };
    }
}

#endif /* !SNAKE_HPP_ */
