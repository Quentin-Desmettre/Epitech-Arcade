/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** sfml
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "IDisplay.hpp"

namespace Arcade {
    class SFML;
};

class Arcade::SFML : public Arcade::IDisplay {
    public:
        SFML();
        ~SFML();
        std::vector<Key> getPressedKeys() override;
        void render(const IGameData &gameData) override;
        void renderMenu(const std::vector<std::string> &games,
        const std::vector<std::string> &graphics, bool isSelectingGame, int selectedIndex) override;
    private:
        void calculateCellSize(int width, int height);
        sf::RenderWindow _window;
        sf::Event _event;
        sf::Font _font;
        sf::Text _text;
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Music _music;
        float _cellSize;
};
