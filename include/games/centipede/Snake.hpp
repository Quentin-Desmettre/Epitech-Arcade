/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Sanke
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <utility>
#include <vector>

namespace Arcade {
    namespace Centipede {
        class Snake {
            public:
                Snake();
                Snake(std::pair<int, int> head, std::pair<int, int> tail, std::vector<std::pair<int, int>> body, bool dir);
                ~Snake();
                void folow(std::pair<int, int> pos);
                void move(char map[25][25]);
                int touch(std::pair<int, int> pos, std::vector<Snake> &snakes);

                std::vector<std::pair<int, int>> getBody() const;
                std::pair<int, int> getHead() const;
            protected:
            private:
                std::pair<int, int> _head;
                std::pair<int, int> _tail;
                std::vector<std::pair<int, int>> _body;
                bool _dir;
        };
    }
}
#endif /* !SNAKE_HPP_ */
