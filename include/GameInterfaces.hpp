/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
#include <string>

/**
 * @brief Namespace containing all the Arcade classes.
 */
namespace Arcade {

    /**
     * @brief Enum of all the possible keys that can be pressed.
     */
    enum Key {
        Unknown = -1, ///< Unhandled key
        A       = 0,  ///< The A key
        B,            ///< The B key
        C,            ///< The C key
        D,            ///< The D key
        E,            ///< The E key
        F,            ///< The F key
        G,            ///< The G key
        H,            ///< The H key
        I,            ///< The I key
        J,            ///< The J key
        K,            ///< The K key
        L,            ///< The L key
        M,            ///< The M key
        N,            ///< The N key
        O,            ///< The O key
        P,            ///< The P key
        Q,            ///< The Q key
        R,            ///< The R key
        S,            ///< The S key
        T,            ///< The T key
        U,            ///< The U key
        V,            ///< The V key
        W,            ///< The W key
        X,            ///< The X key
        Y,            ///< The Y key
        Z,            ///< The Z key
        Num0,         ///< The 0 key
        Num1,         ///< The 1 key
        Num2,         ///< The 2 key
        Num3,         ///< The 3 key
        Num4,         ///< The 4 key
        Num5,         ///< The 5 key
        Num6,         ///< The 6 key
        Num7,         ///< The 7 key
        Num8,         ///< The 8 key
        Num9,         ///< The 9 key
        Escape,       ///< The Escape key
        LControl,     ///< The left Control key
        LShift,       ///< The left Shift key
        LAlt,         ///< The left Alt key
        LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (macOS), ...
        RControl,     ///< The right Control key
        RShift,       ///< The right Shift key
        RAlt,         ///< The right Alt key
        RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (macOS), ...
        Menu,         ///< The Menu key
        LBracket,     ///< The [ key
        RBracket,     ///< The ] key
        Semicolon,    ///< The ; key
        Comma,        ///< The , key
        Period,       ///< The . key
        Apostrophe,   ///< The ' key
        Slash,        ///< The / key
        Backslash,    ///< The \ key
        Grave,        ///< The ` key
        Equal,        ///< The = key
        Hyphen,       ///< The - key (hyphen)
        Space,        ///< The Space key
        Enter,        ///< The Enter/Return keys
        Backspace,    ///< The Backspace key
        Tab,          ///< The Tabulation key
        PageUp,       ///< The Page up key
        PageDown,     ///< The Page down key
        End,          ///< The End key
        Home,         ///< The Home key
        Insert,       ///< The Insert key
        Delete,       ///< The Delete key
        Add,          ///< The + key
        Subtract,     ///< The - key (minus, usually from numpad)
        Multiply,     ///< The * key
        Divide,       ///< The / key
        Left,         ///< Left arrow
        Right,        ///< Right arrow
        Up,           ///< Up arrow
        Down,         ///< Down arrow
        Numpad0,      ///< The numpad 0 key
        Numpad1,      ///< The numpad 1 key
        Numpad2,      ///< The numpad 2 key
        Numpad3,      ///< The numpad 3 key
        Numpad4,      ///< The numpad 4 key
        Numpad5,      ///< The numpad 5 key
        Numpad6,      ///< The numpad 6 key
        Numpad7,      ///< The numpad 7 key
        Numpad8,      ///< The numpad 8 key
        Numpad9,      ///< The numpad 9 key
        F1,           ///< The F1 key
        F2,           ///< The F2 key
        F3,           ///< The F3 key
        F4,           ///< The F4 key
        F5,           ///< The F5 key
        F6,           ///< The F6 key
        F7,           ///< The F7 key
        F8,           ///< The F8 key
        F9,           ///< The F9 key
        F10,          ///< The F10 key
        F11,          ///< The F11 key
        F12,          ///< The F12 key
        F13,          ///< The F13 key
        F14,          ///< The F14 key
        F15,          ///< The F15 key
        Pause,        ///< The Pause key
        KeyCount,     ///< Keep last -- the total number of keyboard keys
    };

    typedef std::unordered_map<std::string, std::string> ControlMap;

    /**
     * @brief Interface of an entity.
     *
     * An entity is the building block of a game; That is to say, anything displayed by a graphical library is an entity (except for scores and controls).
     * For instance, if you want to display walls, create a WallEntity and sets it every position where you want a wall to be.
     * If you want particles, create a ParticleEntity with a small size and a specific texture and add to it as many positions as you want.
     */
    class IEntity {
        public:
            /**
             * @brief Gets all the positions of the entity. These positions are expressed in terms of cell.
             *
             * The entity should be centered in the cell.
             * For an entity in the middle of the screen, the position would be (map_size_x / 2, map_size_y / 2).
            */
            virtual std::vector<std::pair<float, float>> getPosition() const = 0;

            /**
             * @brief Gets the size of the entity. This size is expressed in terms of cell percentage.
             *
             * i.e, a size of (1, 1) means that the entity occupies the whole cell, while a size of (0.5, 0.5) means the entity occupies half of the cell.
            */
            virtual std::pair<float, float> getSize() const = 0;

            /**
             * @brief Gets the texture name of the entity.
             *
             * This method is used to fetch the adequate texture from the texture manager.
             * Example: If the current display name is "libcaca", the game name is "nibbler", and the texture name is "player", the texture manager will look for the texture "assets/nibbler/libcaca/player".
             * The textures should be correctly formatted for the display to be able to load them.
             * If the texture could not be loaded, the behaviour is display-dependent.
             * @return The texture name of the entity.
             */
            virtual std::string getTexture() const = 0;

            /**
             * @brief Gets the rotation of the entity.
             *
             * The rotation is expressed in degrees, and is clockwise.
             * @return The rotation of the entity.
             */
            virtual float getRotation() const = 0;
    };

    /**
     * @brief Interface for the game data.
     *
     * This interface contains all the method required to represent a game.
     */
    class IGameData {
        public:
            /**
             * @brief Gets the differents scores of the game.
             *
             * The key of the map is the name of the score, and the value is the score.
             * For example, a game with a score and a highscore would return a map with the following keys: "score" and "highscore".
             * But, a game with a timer and a lives counter would return a map with the following keys: "timer" and "lives".
             * @return A map containing the scores of the game.
             */
            virtual std::map<std::string, int> getScores() const = 0;

            /**
             * @brief Gets the name of the game.
             *
             * This method is used to (obviously) display the name of the game in the arcade,
             * but it is also used to fetch the game's assets.
             * @return The name of the game.
             */
            virtual std::string getGameName() const = 0;

            /**
             * @brief Gets the entities of the game.
             *
             * The entities are the objects that are displayed on the screen (see Arcade::IEntity).
             * @return A reference to a vector containing the entities of the game.
             */
            virtual std::vector<std::shared_ptr<Arcade::IEntity>> &getEntities() = 0;

            /**
             * @brief Gets the size of the map, in terms of cell.
             *
             * @return A pair containing the size (x / y) of the map, in terms of cell.
             */
            virtual std::pair<int, int> getMapSize() const = 0;

            /**
             * @brief Gets the controls of the game.
             *
             * The controls are the keys that the user can use to play the game.
             * The key of the map is the name of the control, and the value is the key that the user must press to perform the action.
             * For example, a game with a "move left" and a "move right" control would return a map with the following keys: "move left" => "Q" and "move right" => "D".
             * @return
             */
            virtual const ControlMap &getControls() const = 0;

            /**
             * @brief Gets the current state of the game.
             *
             * @return True if the game is over, false otherwise.
             */
            virtual bool isGameOver() const = 0;
    };

    /**
     * @brief The IGame class is the interface that all games must implement.
     *
     * For a game library to be compatible with the arcade, it must contains the following symbols:
     * - "createGame" : A function that returns a pointer to an instance of Arcade::IGame.
     * - "destroyGame" : A function that takes a pointer to an instance of Arcade::IGame and deletes it.
     * The only role of the game library is to perform the game logic, given the user input.
     *
     * Moreover, the best score for this game must be stored in a file named "scores/<game_name>.score"; where <game_name> is the name of the game.
     * This file must contain two lines, the first one being the name of the player, and the second one being the score.
     *
     * @note The game library must handle the best score itself.
     */
    class IGame {
        public:
            virtual ~IGame() = default;

            /**
             * @brief Handles the user input.
             *
             * This method may be used to set the direction of some entities, or to perform some actions.
             * You may also want to store the pressed keys, so that the next time this method is called, you can check if a key was released.
             * @param pressedKeys The list of currently pressed keys
             */
            virtual void handleKeys(const std::vector<Key> &pressedKeys) = 0;

            /**
             * @brief Updates the game state.
             *
             * This method is the core of the game logic. Calls to this method should generally update the content of the game data.
             * IMPORTANT: This method may not be called at a fixed rate, so it should update the game state according to the time elapsed since the last call.
             * @param username
             */
            virtual void update(const std::string &username) = 0;

            /**
             * @brief Gets the game data.
             *
             * @return A reference to the game data (as described by Arcade::IGameData)
             */
            virtual IGameData &getGameData() const = 0;
    };
};

#endif /* !IGAME_HPP_ */
