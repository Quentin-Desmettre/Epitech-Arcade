/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** NibblerEntity
*/

#ifndef NIBBLERENTITY_HPP_
#define NIBBLERENTITY_HPP_
#include "GameInterfaces.hpp"

namespace Arcade {
    namespace Nibbler {
        class Entity : public IEntity {
            public:
                Entity();
                Entity(std::pair<float, float> pos, std::pair<float, float> size, std::string texture, float rotation);
                Entity(const Entity &entity);
                ~Entity();
                void setPosition(std::pair<float, float> pos);
                std::pair<float, float> getPosition() const;
                void setSize(std::pair<float, float> size);
                std::pair<float, float> getSize() const;
                void setTexture(std::string texture);
                std::string getTexture() const;
                void setRotation(float rotation);
                float getRotation() const;
                bool isColliding(Entity &entity) const;
            private:
                std::pair<float, float> _pos;
                std::pair<float, float> _size;
                std::string _texture;
                float _rotation;
                int _direction;
        };
    }
}

#endif /* !NIBBLERENTITY_HPP_ */
