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
        /**
         * @brief A SDL2 font.
         */
        class Font {
        public:
            /**
             * @brief Creates a new font.
             *
             * Once a font has been created, its size / boldness cannot be changed.
             * @param fontPath The path to the font file (.ttf / .otf)
             * @param fontSize The size of the font
             * @param bold Whether the font should be bold or not
             */
            Font(const std::string &fontPath, int fontSize, bool bold = false);
            ~Font();

            /**
             * @brief Gets the raw TTF_Font pointer.
             * @return The raw TTF_Font pointer.
             */
            TTF_Font *getRawFont() const;

        private:
            TTF_Font *_font;
        };
    } // Sdl



#endif //EPITECH_ARCADE_FONT_HPP
