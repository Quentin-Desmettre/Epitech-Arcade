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

class Arcade::Graphics::NCurses::Menu
{
public:
    Menu(Window *parent,
        const std::string &name,
        const Pos &pos,
        const std::vector<std::string> &items,
        int selectedItem,
        Size size = {0, 0});
    ~Menu() = default;

    std::string getName() const;
    std::pair<int, int> getPos() const;
    std::vector<std::string> getItems() const;
    int getSelectedItem() const;

    void setSelected(int selectedItem);

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
