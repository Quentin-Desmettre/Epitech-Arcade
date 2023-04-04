/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include "GameInterfaces.hpp"
#define UNUSED __attribute__((unused))

namespace Arcade {
    class IDisplay;
};


/**
 * @brief Interface for the display.
 *
 * For a display library to be compatible with the Arcade, it must contains the following symbols:
 * - "createDisplay" : a function that returns a pointer to an instance of Arcade::IDisplay
 * - "destroyDisplay" : a function that takes a pointer to an instance of Arcade::IDisplay as parameter and deletes it
 * The only role of a display library is to render the game selection menu or the selected game, and to fetch the pressed keys.
 * IT MUST NOT HANDLE ANY EVENTS (window resizing / closing, key pressed, etc.), NOR ANY GAME LOGIC.
 * This actions are performed by the core.
 */
class Arcade::IDisplay {
    public:
        virtual ~IDisplay() = default;

        /**
         * @brief Get the pressed keys. To indicate an EXIT event, the display library must return a vector containing the Key::ESCAPE key.
         * See Arcade::Key for the list of available keys.
         * @note This method should handle EVERY possible pressed keys, as described in the Arcade::Key enum.
         * @note This method is called every frame.
         * @return A vector containing ALL the currently pressed keys
         */
        virtual std::vector<Key> getPressedKeys() = 0;

        /**
         * @brief Renders the game.
         * This method should perform tne following actions:
         *  - wait sufficient time to reach a static framerate
         *  - draw every entities, scores, controls (described in the gameData parameter)
         * @note This method is called every frame.
         * @param gameData The game data, containing the entities, scores, controls, etc.
         */
        virtual void render(IGameData &gameData) = 0;

        /**
         * @brief Renders the menu.
         * This method should wait sufficient time to reach a static framerate.
         * @note This method is called every frame.
         * @param games The list of available game libraries
         * @param graphics The list of available graphics libraries
         * @param selectedGame The index of the selected game (0 => first game)
         * @param selectedDisplay The index of the selected display (0 => first display)
         * @param controls A map, associating a key (as a string) to an action (as a string). It's only used to inform the user of the controls.
         */
        virtual void renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                                int selectedGame, int selectedDisplay,
                                const ControlMap &controls, const std::string &username, const std::string &bestScoreUsername, int bestScore) = 0;
};

#endif /* !IDISPLAY_HPP_ */
