/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Window
*/

#ifndef EPITECH_ARCADE_WINDOW_HPP
#define EPITECH_ARCADE_WINDOW_HPP
#include <utility>
#include <ncurses.h>
#include <vector>
#include <string>
#include "GameInterfaces.hpp"
#include "libs/ncurses/Texture.hpp"

namespace Arcade::Graphics::NCurses {
    class Window;
} // Arcade

typedef std::pair<int, int> Pos;
typedef std::pair<int, int> Size;

/**
 * @brief A ncurses window.
 */
class Arcade::Graphics::NCurses::Window {
public:
    /**
     * @brief Creates a new window, without any parents, positioned at (0, 0) and taking the whole screen.
     */
    Window();

    /**
     * @brief Creates a new window.
     * @param parent The parent window.
     * @param pos The position of the window.
     * @param size The size of the window.
     */
    Window(Window *parent, const Pos &pos, const Size &size);
    ~Window();

    /**
     * @brief Gets the position of the window.
     * @return
     */
    Pos getPos() const;

    /**
     * @brief Gets the size of the window.
     * @return
     */
    Size getSize();

    /**
     * @brief Draw a box around the window.
     */
    void drawBox();

    /**
     * @brief Draws a string (centered) at the given position.
     * @param text The string to draw.
     * @param pos The position to draw the string at.
     */
    void draw(const std::string &text, const Pos &pos);

    /**
     * @brief Draws a texture at the given position.
     * @param texture The texture to draw.
     * @param pos The position to draw the texture at.
     */
    void draw(const Texture &texture, Pos pos);

    /**
     * @brief Clears the window.
     */
    void clear();

    /**
     * @brief Get the next pressed key.
     * @return
     */
    static Arcade::Key getKey();

private:

    std::pair<int, int> _pos;
    std::pair<int, int> _size;
    std::vector<Window *> _children;
    WINDOW *_win;

    static const std::map<int, Arcade::Key> _keyMap;
    static bool _isInit, _hasColors;
};

#endif //EPITECH_ARCADE_WINDOW_HPP
