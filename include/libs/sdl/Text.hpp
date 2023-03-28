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

class Arcade::Graphics::Sdl::Text: public Arcade::Graphics::Sdl::Sprite {
    public:
        explicit Text(SDL_Renderer *renderer,
                      const Font *font = nullptr,
                      const std::string &text = "",
                      SDL_Color color = {255, 255, 255, 255});
        ~Text();

        void setText(const std::string &text);
        void setFont(const Font &font);
        void setColor(SDL_Color color);
        SpriteSize getSize() const override;

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
