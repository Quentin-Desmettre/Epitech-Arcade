/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Font
*/

#ifndef EPITECH_ARCADE_FONT_HPP
#define EPITECH_ARCADE_FONT_HPP
#include <string>
#include <SDL2/SDL_ttf.h>

namespace Arcade::Graphics::Sdl {
        class Font {
        public:
            Font(const std::string &fontPath, int fontSize, bool bold = false);
            ~Font();

            TTF_Font *getRawFont() const;

        private:
            TTF_Font *_font;
        };
    } // Sdl



#endif //EPITECH_ARCADE_FONT_HPP
