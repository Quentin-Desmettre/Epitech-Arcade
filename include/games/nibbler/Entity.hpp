/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** NibblerEntity
*/

#ifndef NIBBLERENTITY_HPP_
#define NIBBLERENTITY_HPP_
#include "GameInterfaces.hpp"

namespace Arcade::Games::Nibbler {
    /**
     * @brief A Nibbler Entity.
     */
    class Entity : public IEntity {
        public:
            /**
             * @brief Creates a new Entity.
             */
            Entity();

            /**
             * @brief Creates a new Entity.
             * @param pos The position of the Entity.
             * @param size The size of the Entity.
             * @param texture The texture of the Entity.
             * @param rotation The rotation of the Entity.
             */
            Entity(std::vector<std::pair<float, float>> pos, std::pair<float, float> size, std::string texture, float rotation);

            /**
             * @brief Copy constructor.
             * @param entity The Entity to copy.
             */
            Entity(const Entity &entity);
            ~Entity();

            /**
             * @see IEntity::getPosition
             */
            std::vector<std::pair<float, float>> getPosition() const override;

            /**
             * @see IEntity::getSize
             */
            std::pair<float, float> getSize() const override;

            /**
             * @see IEntity::getTexture
             */
            std::string getTexture() const override;

            /**
             * @see IEntity::getRotation
             */
            float getRotation() const override;

            /**
             * @brief Sets the position of the Entity.
             * @param pos The new position of the Entity.
             */
            void setPosition(std::vector<std::pair<float, float>> pos);

            /**
             * @brief Sets the size of the Entity.
             * @param size The new size of the Entity.
             */
            void setSize(std::pair<float, float> size);

            /**
             * @brief Sets the texture of the Entity.
             * @param texture The new texture of the Entity.
             */
            void setTexture(std::string texture);

            /**
             * @brief Sets the rotation of the Entity.
             * @param rotation The new rotation of the Entity.
             */
            void setRotation(float rotation);
        private:
            std::vector<std::pair<float, float>> _pos;
            std::pair<float, float> _size;
            std::string _texture;
            float _rotation;
            int _direction;
    };
}

#endif /* !NIBBLERENTITY_HPP_ */
