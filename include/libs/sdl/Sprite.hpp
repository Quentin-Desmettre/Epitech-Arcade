/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Sprite
*/

#ifndef EPITECH_ARCADE_SPRITE_HPP
#define EPITECH_ARCADE_SPRITE_HPP
#include "sdl/Texture.hpp"

namespace Arcade {
    namespace Sdl {
        class Sprite;
        static const auto
            White = SDL_Color{255, 255, 255, 255},
            Black = SDL_Color{0, 0, 0, 255},
            Red = SDL_Color{255, 0, 0, 255},
            Green = SDL_Color{0, 255, 0, 255},
            Blue = SDL_Color{0, 0, 255, 255},
            Yellow = SDL_Color{255, 255, 0, 255},
            Magenta = SDL_Color{255, 0, 255, 255},
            Cyan = SDL_Color{0, 255, 255, 255},
            Transparent = SDL_Color{0, 0, 0, 0}
        ;
    } // Arcade
} // Sdl

typedef std::pair<double, double> SpriteSize;

class Arcade::Sdl::Sprite {
    public:
        explicit Sprite(const Texture &texture);
        explicit Sprite();
        ~Sprite() = default;

        void setTexture(const Texture &texture);
        void setSize(const SpriteSize &size);
        void setTextureRect(const TextureRect &rect);
        void setPosition(const SpriteSize &position);

        virtual const Texture &getTexture() const;
        virtual SpriteSize getSize() const;

        virtual const TextureRect &getTextureRect() const;
        const SpriteSize &getPosition() const;

    protected:
        const Texture *_texture;
        SpriteSize _size, _position;
        TextureRect _textureRect;
};

#endif //EPITECH_ARCADE_SPRITE_HPP
