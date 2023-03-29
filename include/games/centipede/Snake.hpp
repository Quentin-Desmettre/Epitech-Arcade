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

namespace Arcade::Games::Centipede {
    /**
     * @brief A Centipede snake.
     */
    class Snake {
        public:
            /**
             * @brief creates a new centipede
             */
            Snake();

            /**
             * @brief creates a new centipede
             * @param head Position of the head
             * @param tail Position of the tail
             * @param body Position of the body
             * @param dir Direction of the snake
             */
            Snake(std::pair<int, int> head, std::pair<int, int> tail, std::vector<std::pair<int, int>> body, bool dir);
            ~Snake();

            /**
             * @brief Make the centipede goes to a position
             * @param pos Position to go
             */
            void folow(std::pair<int, int> pos);

            /**
             * @brief Make the centipede move
             * @param map Map of the game
             */
            void move(char map[25][25]);

            /**
             * @brief Check if the centipede touch a position
             * @param pos Position to check
             * @param snakes List of the snakes
             * @return 0 if the centipede is not dead, 1 if the centipede is dead, 2 if the centipede is dead and the player win
             */
            int touch(std::pair<int, int> pos, std::vector<Snake> &snakes);

            /**
             * @brief Get the positions of the snake cells
             * @return List of the positions
             */
            std::vector<std::pair<int, int>> getBody() const;

            /**
             * @brief Get the position of the head
             * @return Position of the head
             */
            std::pair<int, int> getHead() const;
        protected:
        private:
            std::pair<int, int> _head;
            std::pair<int, int> _tail;
            std::vector<std::pair<int, int>> _body;
            bool _dir;
    };
}
#endif /* !SNAKE_HPP_ */
