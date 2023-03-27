/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** NibblerEntity
*/

#ifndef CENTIPEDEENTITY_HPP_
#define CENTIPEDEENTITY_HPP_
#include "GameInterfaces.hpp"

namespace Arcade {
    namespace Centipede {
        class Entity : public IEntity {
            public:
                Entity();
                Entity(std::vector<std::pair<float, float>> pos, std::pair<float, float> size, std::string texture, float rotation);
                Entity(const Entity &entity);
                ~Entity();
                void setPosition(std::vector<std::pair<float, float>> pos);
                std::vector<std::pair<float, float>> getPosition() const;
                void setSize(std::pair<float, float> size);
                std::pair<float, float> getSize() const;
                void setTexture(std::string texture);
                std::string getTexture() const;
                void setRotation(float rotation);
                float getRotation() const;
            private:
                std::vector<std::pair<float, float>> _pos;
                std::pair<float, float> _size;
                std::string _texture;
                float _rotation;
                int _direction;
        };
    }
}

#endif /* !NIBBLERENTITY_HPP_ */
