/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Menu
*/

#include "Menu.hpp"

Arcade::Graphics::NCurses::Menu::Menu(Window *parent,
                   const std::string &name,
                   const Pos &pos,
                   const std::vector<std::string> &items,
                   int selectedItem,
                   Size size):
    _name(name), _pos(pos), _items(items), _selectedItem(selectedItem), _parent(parent)
{
    // Create title and items windows
    Size titleSize{size.first, 3};
    Pos itemsPos{pos.first, pos.second + 3};
    Size itemsSize{size.first, size.second - 3};
    _titleWin = std::make_unique<Window>(parent, pos, titleSize);
    _itemsWin = std::make_unique<Window>(parent, itemsPos, itemsSize);
}

void Arcade::Graphics::NCurses::Menu::render()
{
    // Draw title
    auto size = _titleWin->getSize();
    _titleWin->clear();
    _titleWin->drawBox();
    _titleWin->draw(_name, {(size.first - _name.size()) / 2, 1});

    // Draw items
    _itemsWin->clear();
    _itemsWin->drawBox();
    for (std::size_t i = 0; i < _items.size(); i++)
        _itemsWin->draw(_items[i], {5, i + 1});
    if (_selectedItem >= 0)
        _itemsWin->draw("->", {2, _selectedItem + 1});
}

std::string Arcade::Graphics::NCurses::Menu::getName() const
{
    return _name;
}

std::pair<int, int> Arcade::Graphics::NCurses::Menu::getPos() const
{
    return _pos;
}

std::vector<std::string> Arcade::Graphics::NCurses::Menu::getItems() const
{
    return _items;
}

int Arcade::Graphics::NCurses::Menu::getSelectedItem() const
{
    return _selectedItem;
}

void Arcade::Graphics::NCurses::Menu::setSelected(int selectedItem)
{
    _selectedItem = selectedItem;
}
