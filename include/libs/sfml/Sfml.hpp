/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** sfml
*/

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "IDisplay.hpp"

/**
 * @brief The SFML graphical library.
 */
namespace Arcade::Graphics::SFML {
    class SFML;
};

/**
 * @brief The SFML graphical library.
 */
class Arcade::Graphics::SFML::SFML : public Arcade::IDisplay {
    public:
        /**
         * @brief Creates a new SFML graphical library.
         */
        SFML();
        ~SFML() override;

        /**
         * @see Arcade::IDisplay::getPressedKeys()
         * @return
         */
        std::vector<Key> getPressedKeys() override;

        /**
         * @see Arcade::IDisplay::render()
         */
        void render(IGameData &gameData) override;

        /**
         * @see Arcade::IDisplay::renderMenu()
         */
        void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                        int selectedGame, int selectedDisplay,
                        const ControlMap &controls, const std::string &username, const std::string &bestScoreUsername, int bestScore) override;

    private:
        std::map<std::string, std::unique_ptr<sf::Texture>> _textureMap;
        bool loadTexture(std::string texturePath);
        void calculateCellSize(int width, int height);
        void centerTextOrigin();
        void drawTextWithColor(sf::Color color);
        void drawRect(sf::Vector2f size, sf::Vector2f position);
        void drawLine(sf::Vector2f start, sf::Vector2f end);
        void drawInfoPanel(IGameData &gameData);
        std::string truncString(std::string str);
        void setupMenu();
        sf::RenderWindow _window;
        sf::Event _event;
        sf::Font _font;
        sf::Text _text;
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Music _music;
        sf::RectangleShape _rectangle;
        float _cellSize;
        bool _isMenu;
};

/**
 * @brief Creates a new SFML graphical library.
 * See Arcade::IDisplay::createDisplay() for more information.
 */
extern "C" void *createDisplay();

/**
 * @brief Deletes a SFML graphical library.
 * See Arcade::IDisplay::deleteDisplay() for more information.
 */
extern "C" void deleteDisplay(void *display);
