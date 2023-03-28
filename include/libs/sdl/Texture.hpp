/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Texture
*/

#ifndef EPITECH_ARCADE_TEXTURE_HPP
#define EPITECH_ARCADE_TEXTURE_HPP
#include <string>
#include <utility>
#include <SDL2/SDL.h>

/**
 * @brief The namespace containing all the graphical libraries.
 */
namespace Arcade::Graphics{}

namespace Arcade::Graphics::Sdl {
    class Texture;
    struct TextureRect;
} // Sdl

typedef std::pair<int, int> TextureSize;

struct Arcade::Graphics::Sdl::TextureRect {
    int left, top, width, height;
};

/**
 * @brief A wrapper around a SDL2 texture.
 */
class Arcade::Graphics::Sdl::Texture {
    public:
        /**
         * @brief Creates a new texture.
         * @param texturePath The path to the texture file.
         * @param renderer The renderer to use to create the texture.
         */
        explicit Texture(const std::string &texturePath, SDL_Renderer *renderer);
        ~Texture();

        /**
         * @brief Gets the size of the texture.
         * @return The size of the texture.
         */
        TextureSize getSize() const;

        /**
         * @brief Gets the raw SDL_Texture pointer.
         * @return The raw SDL_Texture pointer.
         */
        SDL_Texture *getRawTexture() const;

    private:
        TextureSize _size;
        SDL_Texture *_texture;
};

#endif //EPITECH_ARCADE_TEXTURE_HPP
