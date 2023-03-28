/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Menu
*/

#ifndef EPITECH_ARCADE_MENU_HPP
#define EPITECH_ARCADE_MENU_HPP
#include <utility>
#include <string>
#include <vector>
#include "Window.hpp"
#include <memory>

namespace Arcade::Graphics::NCurses {
    class Menu;
} // Arcade

/**
 * @brief A ncurses menu.
 *
 * A menu is a contains a name, a position, a list of items and a selected item, and a size.
 */
class Arcade::Graphics::NCurses::Menu
{
public:

    /**
     * @brief Creates a new menu.
     * @param parent The parent window.
     * @param name The name of the menu.
     * @param pos The position of the menu.
     * @param items The items of the menu.
     * @param selectedItem The selected item.
     * @param size The size of the menu.
     */
    Menu(Window *parent,
        const std::string &name,
        const Pos &pos,
        const std::vector<std::string> &items,
        int selectedItem,
        Size size = {0, 0});
    ~Menu() = default;

    /**
     * @brief Gets the name of the menu.
     * @return
     */
    std::string getName() const;

    /**
     * @brief Gets the position of the menu.
     * @return
     */
    std::pair<int, int> getPos() const;

    /**
     * @brief Gets the items of the menu.
     * @return
     */
    std::vector<std::string> getItems() const;

    /**
     * @brief Gets the selected item.
     * @return
     */
    int getSelectedItem() const;

    /**
     * @brief Sets the currently selected item.
     * @param selectedItem The selected item.
     */
    void setSelected(int selectedItem);

    /**
     * @brief Renders the menu
     *
     * This method draws the menu on the parent window, with a box around it.
     */
    void render();

private:
    std::string _name;
    std::pair<int, int> _pos;
    std::vector<std::string> _items;
    int _selectedItem;
    Window *_parent;

    using UniqueWindow = std::unique_ptr<Window>;
    UniqueWindow _titleWin, _itemsWin;
};

#endif //EPITECH_ARCADE_MENU_HPP
