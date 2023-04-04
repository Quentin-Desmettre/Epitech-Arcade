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

/**
 * @brief A wrapper around the SDL2 library.
 */
namespace Arcade::Graphics::Sdl {
    class Sdl;
} // Sdl

/**
 * @brief The SDL2 graphical library.
 */
class Arcade::Graphics::Sdl::Sdl: public Arcade::IDisplay {
public:
    /**
     * @brief Creates a new SDL2 graphical library.
     */
    Sdl();
    ~Sdl() override;

    /**
     * @see Arcade::IDisplay::getPressedKeys()
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

    /**
     * @brief Unloads all the textures.
     *
     * This method is only called when the SDL2 library is unloaded (via deleteDisplay)
     */
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

/**
 * @brief Creates a new SDL2 graphical library.
 * See Arcade::IDisplay::createDisplay() for more information.
 * @return A pointer to the new SDL2 graphical library.
 */
extern "C" void *createDisplay();

/**
 * @brief Deletes a SDL2 graphical library.
 * See Arcade::IDisplay::deleteDisplay() for more information.
 * @param display The SDL2 graphical library to delete (which was created with createDisplay).
 */
extern "C" void deleteDisplay(void *display);

#endif //EPITECH_ARCADE_SDL_HPP
