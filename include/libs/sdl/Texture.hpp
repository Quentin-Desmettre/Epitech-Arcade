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

namespace Arcade {
    namespace Sdl {
        class Texture;
        struct TextureRect;
    } // Arcade
} // Sdl

typedef std::pair<int, int> TextureSize;

struct Arcade::Sdl::TextureRect {
    int left, top, width, height;
};

class Arcade::Sdl::Texture {
    public:
        explicit Texture(const std::string &texturePath, SDL_Renderer *renderer);
        ~Texture();

        TextureSize getSize() const;
        SDL_Texture *getRawTexture() const;

    private:
        TextureSize _size;
        SDL_Texture *_texture;
};

#endif //EPITECH_ARCADE_TEXTURE_HPP
