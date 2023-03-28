/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Text
*/

#ifndef EPITECH_ARCADE_TEXT_HPP
#define EPITECH_ARCADE_TEXT_HPP
#include <string>
#include "sdl/Font.hpp"
#include "sdl/Sprite.hpp"
#include <stdexcept>

namespace Arcade::Graphics::Sdl {
    class Text;
} // Sdl

/**
 * @brief A text, with a font, a color and a text.
 */
class Arcade::Graphics::Sdl::Text: public Arcade::Graphics::Sdl::Sprite {
    public:
        /**
         * @brief Creates a new text.
         * @param renderer The SDL2 rendered to use
         * @param font The font to use
         * @param text The text to display
         * @param color The color of the text
         */
        explicit Text(SDL_Renderer *renderer,
                      const Font *font = nullptr,
                      const std::string &text = "",
                      SDL_Color color = {255, 255, 255, 255});
        ~Text();

        /**
         * @brief Sets the text.
         * @param text The new text
         */
        void setText(const std::string &text);

        /**
         * @brief Sets the font.
         * @param font The new font
         */
        void setFont(const Font &font);

        /**
         * @brief Sets the color.
         * @param color The new color
         */
        void setColor(SDL_Color color);

        /**
         * @brief Gets the size of the text
         * @return The size of the text
         */
        SpriteSize getSize() const override;

        /**
         * @brief Gets the raw SDL_Texture pointer.
         * @note You should call this method to update the content of the text.
         * @return The raw SDL_Texture pointer.
         */
        SDL_Texture *getRawTexture();

    private:
        const TextureRect &getTextureRect() const override { throw std::runtime_error("Text::getTextureRect() should not be used"); }
        const Texture &getTexture() const override { throw std::runtime_error("Text::getTexture() should not be used"); }

        const Font *_font;
        std::string _text;
        SDL_Color _color;
        bool _isSurfaceUpdated;

        SDL_Surface *_surface;
        SDL_Texture *_texture;
        SDL_Renderer *_renderer;
};

#endif //EPITECH_ARCADE_TEXT_HPP
