/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Sdl
*/

#ifndef EPITECH_ARCADE_SDL_HPP
#define EPITECH_ARCADE_SDL_HPP
#include "IDisplay.hpp"
#include "sdl/RenderWindow.hpp"
#include "sdl/Font.hpp"
#include "sdl/Text.hpp"
#include "sdl/Sprite.hpp"
#include <memory>

namespace Arcade {
    namespace Sdl {
        class Sdl;
    } // Arcade
} // Sdl

class Arcade::Sdl::Sdl: public Arcade::IDisplay {
public:
    Sdl();
    ~Sdl() override;

    std::vector<Key> getPressedKeys();
    void render(IGameData &gameData) override;
    void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                    int selectedGame, int selectedGraph, const ControlMap &controls) override;

    static void unloadTextures();
private:
    // Globals
    RenderWindow _window;
    Font _globalFont, _boldGlobalFont, _gameOverFont;

    // Menu
    using UniqueText = std::unique_ptr<Text>;
    UniqueText _graphTitle, _gameTitle, _controlsTitle, _infoPanelTitle, _scoreText, _gameOverText;
    std::vector<UniqueText> _graphItems, _gameItems, _controlsItems;
    std::vector<std::string> _graphNames, _gameNames;
    ControlMap _controls;
    std::unique_ptr<Texture> _menuBackgroundTexture;
    Sprite _menuBackground;

    // Game
    static std::map<std::string, std::unique_ptr<Texture>> _textures;

    // Utility
    const static std::map<int, Key> _keyMap;
    void createMenus(const std::vector<std::string> &games, const std::vector<std::string> &graphics, const ControlMap &controls);
    void drawMenuTitlesAndBg();
    void drawMenuItems(int selectedGame, int selectedGraph);
    static std::string simplifyName(const std::string &name);
    static double calculateCellSize(int width, int height);
    static std::string texturePath(const IEntity &entity, const std::string &gameName);
    void drawInfoPanel(Arcade::IGameData &gameData);
};

#endif //EPITECH_ARCADE_SDL_HPP
