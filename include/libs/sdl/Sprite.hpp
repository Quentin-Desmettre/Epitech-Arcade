/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Sprite
*/

#ifndef EPITECH_ARCADE_SPRITE_HPP
#define EPITECH_ARCADE_SPRITE_HPP
#include "sdl/Texture.hpp"

namespace Arcade::Graphics::Sdl {
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
    } // Sdl

typedef std::pair<double, double> SpriteSize;

/**
 * @brief A sprite, with a texture, a size, a position and a texture rect.
 */
class Arcade::Graphics::Sdl::Sprite {
    public:
        /**
         * @brief Creates a new sprite, with the size of the texture.
         * @param texture The texture of the sprite.
         */
        explicit Sprite(const Texture &texture);

        /**
         * @brief Creates a new sprite, with no texture.
         */
        explicit Sprite();
        ~Sprite() = default;

        /**
         * @brief Sets the texture of the sprite.
         *
         * The size of the sprite will be set to the size of the texture.
         * @param texture The new texture of the sprite.
         */
        void setTexture(const Texture &texture);

        /**
         * @brief Sets the size of the sprite.
         * @param size The new size of the sprite.
         */
        void setSize(const SpriteSize &size);

        /**
         * @brief Sets the zone of the texture to use.
         * @param rect The new texture rect of the sprite.
         */
        void setTextureRect(const TextureRect &rect);

        /**
         * @brief Sets the position of the sprite.
         * @param position The new position of the sprite.
         */
        void setPosition(const SpriteSize &position);

        /**
         * @brief Gets the texture of the sprite.
         * @return The texture of the sprite.
         */
        virtual const Texture &getTexture() const;

        /**
         * @brief Gets the size of the sprite.
         * @return The size of the sprite.
         */
        virtual SpriteSize getSize() const;

        /**
         * @brief Gets the texture rect of the sprite.
         * @return The texture rect of the sprite.
         */
        virtual const TextureRect &getTextureRect() const;

        /**
         * @brief Gets the position of the sprite.
         * @return The position of the sprite.
         */
        const SpriteSize &getPosition() const;

    protected:
        const Texture *_texture;
        SpriteSize _size, _position;
        TextureRect _textureRect;
};

#endif //EPITECH_ARCADE_SPRITE_HPP
