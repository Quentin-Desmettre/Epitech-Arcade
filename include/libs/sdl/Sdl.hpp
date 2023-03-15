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

    std::vector<Key> getPressedKeys() override;
    void render(const IGameData &gameData) override;
    void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics, bool isSelectingGame, int selectedIndex, const ControlMap &controls) override;

private:
    // Globals
    RenderWindow _window;
    Font _globalFont, _boldGlobalFont;

    // Menu
    using UniqueText = std::unique_ptr<Text>;
    UniqueText _graphTitle, _gameTitle, _controlsTitle;
    std::vector<UniqueText> _graphItems, _gameItems, _controlsItems;
    std::vector<std::string> _graphNames, _gameNames;
    ControlMap _controls;

    Texture _menuBackgroundTexture;
    Sprite _menuBackground;

    static std::map<std::string, std::unique_ptr<Texture>> _spriteMap;
    const static std::map<SDL_Scancode, Key> _keyMap;

    void createMenus(const std::vector<std::string> &games, const std::vector<std::string> &graphics, const ControlMap &controls);
    void drawMenuTitlesAndBg();
    void drawMenuItems(bool isSelectingGame, int selectedIndex);
    static std::string simplifyName(const std::string &name);
};

#endif //EPITECH_ARCADE_SDL_HPP
